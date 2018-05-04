#include <fstream>
#include <list>
#include <ostream>

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

void Schema::addBlock(Block *blck) {
    unsigned int id = ++this->block_id_gen;
    this->blocks[id] = blck;
}

void Schema::loadBlck(Block *blck) { this->blocks[blck->getID()] = blck; }

void Schema::loadConn(Connection *conn) { this->connections[conn->getID()] = conn; }

BlockAdd *Schema::newAddBlock(unsigned int in_size) {
    unsigned int id = ++this->block_id_gen;

    auto new_blck = new BlockAdd{id, in_size};
    this->blocks[id] = new_blck;

    return new_blck;
}

BlockMul *Schema::newMulBlock(unsigned int in_size) {
    unsigned int id = ++this->block_id_gen;

    auto new_blck = new BlockMul{id, in_size};
    this->blocks[id] = new_blck;

    return new_blck;
}

BlockSub *Schema::newSubBlock() {
    unsigned int id = ++this->block_id_gen;

    auto new_blck = new BlockSub{id};
    this->blocks[id] = new_blck;

    return new_blck;
}

BlockOut *Schema::newOutBlock(double output) {
    unsigned int id = ++this->block_id_gen;

    auto new_blck = new BlockOut{id, output};
    this->blocks[id] = new_blck;

    return new_blck;
}

BlockDiv *Schema::newDivBlock() {
    unsigned int id = ++this->block_id_gen;

    auto new_blck = new BlockDiv{id};
    this->blocks[id] = new_blck;

    return new_blck;
}

BlockPow *Schema::newPowBlock() {
    unsigned int id = ++this->block_id_gen;

    auto new_blck = new BlockPow{id};
    this->blocks[id] = new_blck;

    return new_blck;
}

BlockNeg *Schema::newNegBlock() {
    unsigned int id = ++this->block_id_gen;

    auto new_blck = new BlockNeg{id};
    this->blocks[id] = new_blck;

    return new_blck;
}



bool Schema::deleteBlock(Block *b) {
    if (b != nullptr) {
        unsigned b_ID = b->getID();
        std::vector<Connection *> inputs = b->getInputs();
        for (const auto &i : inputs) {
            this->deleteConnection(i);
        }

        for (auto &i : this->connections) {
            if (i.second->getInput() == b) {
                this->deleteConnection(i.second);
            }
        }

        delete b;
        this->blocks.erase(b_ID);

        return true;
    } else {
        return false;
    }
}

/* Returns ID of the new connection */
Connection *Schema::newConnection(Block *in, Block *out, unsigned int pos) {
    /* is it possible?*/
    // TODO

    /* generate new id */
    unsigned int id = ++this->conn_id_gen;

    /* add to connections vector */
    auto new_con = new Connection{id, in, out, pos};
    this->connections[id] = new_con;

    /* tell blocks that they have new connection*/
    out->setNewInput(new_con, pos);
    return new_con;
}

Connection *Schema::newConnection(Block *in, Block *out) {
    unsigned index = out->getFirstFreeIdx();
    return this->newConnection(in, out, index);
}

bool Schema::deleteConnection(Connection *conn) {
    if (conn != nullptr) {
        unsigned ID = conn->getID();

        Block *blck = conn->getOutBlock();
        unsigned int index = conn->getIdx();

        blck->unsetInput(index);
        this->connections.erase(ID);

        return true;
    } else {
        return false;
    }
}

Block *Schema::getBlckByID(unsigned int ID) { return this->blocks[ID]; }

Connection *Schema::getConByID(unsigned int ID) { return this->connections[ID]; }

bool Schema::compute() {
    /* Here are blocks that have not been calcualted yet */
    /* Output Blocks are ignored */
    std::list<Block *> to_calculate{};
    for (const auto &i : this->blocks) {
        if (i.second->getType() != OUT) {
            to_calculate.push_back(i.second);
        }
    }

    bool cont{true};

    while (cont) {
        cont = false;
        // prejdi to_calculate
        // skus vypocitat
        // ked sa da, ohlas ze sa aspon 1 zmenilo a vymaz to z to_calculate
        // ked nie, tak chod na dalsi
        for (auto i = to_calculate.begin(); i != to_calculate.end();) {
            if ((*i)->tryCompute()) {
                i = to_calculate.erase(i);
                cont = true;
            } else {
                i++;
            }
        }
    }

    return to_calculate.empty(); // ked je prazdne tak sa podarilo priradit vsetko
}
