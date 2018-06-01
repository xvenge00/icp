/**
 * @file schema.cpp
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 */

#include <fstream>
#include <list>
#include <ostream>

#include "block.h"
#include "connection.h"
#include "schema.h"
#include "debug.h"

Schema::Schema() {
    this->blocks = std::map<int, Block *>{};
    this->connections = std::map<int, Connection *>{};
    this->block_id_gen = 0;
    this->conn_id_gen = 0;
}

Schema::~Schema() {
    clear();
}

void Schema::clear() {
    blocks.clear();
    connections.clear();
}

void Schema::addBlock(Block *blck) {
    unsigned newID = blck->getID();
    if (newID > block_id_gen + 1) {
        block_id_gen = newID + 1;
    }

    this->blocks[newID] = blck;
}

void Schema::addConnection(Connection *conn) {
    unsigned newID = conn->getID();
    if (newID > conn_id_gen) {
        conn_id_gen = newID + 1;
    }

    this->connections[newID] = conn;
}

//void Schema::loadBlck(Block *blck) { this->blocks[blck->getID()] = blck; }

//void Schema::loadConn(Connection *conn) { this->connections[conn->getID()] = conn; }

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
        // delete input connections
        std::vector<Connection *> inputs = b->getInputs();
        for (const auto &i : inputs) {
            this->deleteConnection(i);
        }

        //delete all connections that lead from block b
        for (auto &i : this->connections) {
            if (i.second->getInput() == b) {
                this->deleteConnection(i.second);
            }
        }

        //delete block b
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
    if (pos >= out->getInputSize()) {
        return nullptr;
    }

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

void Schema::unset() {
    for (auto &i : blocks) {
        if (i.second->getType() != OUT ){
            i.second->unset();
        }
    }
}

bool Schema::compute() {
    beforeCalc();

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

bool Schema::beforeCalc() {
    unset();
    this->to_calculate = std::list<Block *>{};
    for (const auto &i : this->blocks) {
        if (i.second->getType() != OUT) {
            to_calculate.push_back(i.second);
        }
    }
    LOGD("to_calculate filled\n");
}

bool Schema::step() {
    for (auto i = to_calculate.begin(); i != to_calculate.end();) {
        if ((*i)->tryCompute()) {
            i = to_calculate.erase(i);
            return true;
        } else {
            i++;
        }
    }

    return to_calculate.empty();
}

void Schema::clearSchema() {
    for (const auto &i : blocks) {
        this->deleteBlock(i.second);
    }
}
