#include <fstream>
#include <ostream>
#include <list>

#include "block.h"
#include "connection.h"
#include "schema.h"

Schema::Schema() {
    this->blocks = std::map<int, Block *>{};
    this->connections = std::map<int, Connection *>{};
    this->block_id_gen = 0;
    this->conn_id_gen = 0;
}

Schema::~Schema() {
    for (const auto &i : this->blocks) {
        delete i.second;
    }
    for (const auto &i : this->connections) {
        delete i.second;
    }
}

void Schema::save(const string &file_name) {
    ofstream out_stream;
    out_stream.open(file_name);     //TODO if fail

    out_stream << *this;
    out_stream.close();
}

void Schema::loadBlck(Block *blck) { this->blocks[blck->getID()] = blck; }

void Schema::loadConn(Connection *conn) {
    this->connections[conn->getID()] = conn;
}

void Schema::load(const string &file_name) {
    ifstream s;
    s.open(file_name);  //TODO if fail

    s >> *this;

    s.close();
}

unsigned int Schema::newAddBlock(unsigned int in_size, int pos_x, int pos_y) {
    unsigned int id = ++this->block_id_gen;

    auto new_blck = new BlockAdd{id, pos_x, pos_y, in_size};
    this->blocks[id] = new_blck;

    return id;
}

unsigned int Schema::newMulBlock(unsigned int in_size, int pos_x, int pos_y) {
    unsigned int id = ++this->block_id_gen;

    auto new_blck = new BlockMul{id, pos_x, pos_y, in_size};
    this->blocks[id] = new_blck;

    return id;
}

unsigned int Schema::newSubBlock(int pos_x, int pos_y) {
    unsigned int id = ++this->block_id_gen;

    auto new_blck = new BlockSub{id, pos_x, pos_y};
    this->blocks[id] = new_blck;

    return id;
}

unsigned int Schema::newOutBlock(double output, int pos_x, int pos_y) {
    unsigned int id = ++this->block_id_gen;

    auto new_blck = new BlockOut{id, pos_x, pos_y, output};
    this->blocks[id] = new_blck;

    return id;
}

bool Schema::deleteBlock(unsigned int ID) {
    Block *to_del = this->getBlckByID(ID);
    std::vector<Connection *>inputs = to_del->getInputs();
    for (const auto &i : inputs) {
//        to_del->unsetInput(i->getIdx());
        this->deleteConnection(i->getID());
    }

    for (auto &i : this->connections) {
        if (i.second->getInput() == to_del) {
            this->deleteConnection(static_cast<unsigned int>(i.first));
        }
    }

    delete to_del;
    this->blocks.erase(ID);

    return true;
}

/* Returns ID of the new connection */
unsigned int Schema::newConnection(Block *in, Block *out, unsigned int pos) {
    /* is it possible?*/
    // TODO

    /* generate new id */
    unsigned int id = ++this->conn_id_gen;

    /* add to connections vector */
    auto new_con = new Connection{id, in, out, pos};
    this->connections[id] = new_con;

    /* tell blocks that they have new connection*/
    out->setNewInput(this->connections[id],pos);
    return id;
}

bool Schema::deleteConnection(unsigned int ID) {
    Connection *conn = this->getConByID(ID);
    if (conn != nullptr) {
        Block *blck = conn->getOutBlock();
        unsigned int index = conn->getIdx();

        blck->unsetInput(index);
        this->connections.erase(ID);

        return true;
    }
    return false;
}

Block *Schema::getBlckByID(unsigned int ID) { return this->blocks[ID]; }

Connection *Schema::getConByID(unsigned int ID) { return this->connections[ID]; }

bool Schema::compute() {
    /* Here are blocks that have not been calcualted yet */
    /* Output Blocks are ignored */
    std::list<Block *> to_calculate{};
    for (const auto &i : this->blocks) {
        if (i.second->getType() != OUT){
            to_calculate.push_back(i.second);
        }
    }

    bool cont{true};
    bool tmp{};

    while (cont) {
        cont = false;
        // prejdi to_calculate
        // skus vypocitat
        // ked sa da, ohlas ze sa aspon 1 zmenilo a vymaz to z to_calculate
        // ked nie, tak chod na dalsi
        for (auto i = to_calculate.begin(); i != to_calculate.end();) {
            tmp = (*i)->tryCompute();
            if (tmp) {
                i = to_calculate.erase(i);
                cont = true;
            } else {
                i++;
            }
        }
    }

    return to_calculate.empty();    //ked je prazdne tak sa podarilo priradit vsetko
}
