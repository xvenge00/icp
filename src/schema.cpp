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
        delete i.second;    //TODO delete called on 'Block' that is abstract but has non-virtual destructor
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

void Schema::loadConn(Connection *conn) { this->connections[conn->getID()] = conn; }

void Schema::load(const string &file_name) {
    ifstream s;
    s.open(file_name);  //TODO if fail

    s >> *this;

    s.close();
}

//uint32_t Schema::newBlock(blck_type type, int pos_x, int pos_y) {
//    static uint32_t id_count{0};
//    id_count++;
//
//    auto new_blck = new Block{id_count, pos_x, pos_y, type};
//    this->blocks[id_count] = new_blck;
//    return id_count;
//}

uint32_t Schema::newAddBlock(uint8_t in_size, int pos_x, int pos_y) {
    uint32_t id = ++this->block_id_gen;

    auto new_blck = new BlockAdd{id, pos_x, pos_y, in_size};
    this->blocks[id] = new_blck;

    return id;
}

uint32_t Schema::newMulBlock(uint8_t in_size, int pos_x, int pos_y) {
    uint32_t id = ++this->block_id_gen;

    auto new_blck = new BlockMul{id, pos_x, pos_y, in_size};
    this->blocks[id] = new_blck;

    return id;
}

uint32_t Schema::newSubBlock(int pos_x, int pos_y) {
    uint32_t id = ++this->block_id_gen;

    auto new_blck = new BlockSub{id, pos_x, pos_y};
    this->blocks[id] = new_blck;

    return id;
}

uint32_t Schema::newOutBlock(double output, int pos_x, int pos_y) {
    uint32_t id = ++this->block_id_gen;

    auto new_blck = new BlockOut{id, pos_x, pos_y, output};
    this->blocks[id] = new_blck;

    return id;
}

/* Returns ID of the new connection */
uint32_t Schema::newConnection(Block *in, Block *out, uint8_t pos) {
    /* is it possible?*/
    // TODO

    /* generate new id */
    uint32_t id = ++this->conn_id_gen;

    /* add to connections vector */
    auto new_con = new Connection{id, in, out};
    this->connections[id] = new_con;

    /* tell blocks that they have new connection*/
    out->setNewInput(this->connections[id],pos);
    return id;
}

Block *Schema::getBlckByID(uint32_t ID) { return this->blocks[ID]; }

Connection *Schema::getConByID(uint32_t ID) { return this->connections[ID]; }

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
