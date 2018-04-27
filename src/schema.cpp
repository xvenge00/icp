#include <fstream>
#include <ostream>

#include "block.h"
#include "connection.h"
#include "schema.h"

Schema::Schema() {
    this->blocks = std::map<int, Block *>{};
    this->connections = std::map<int, Connection *>{};
}

Schema::~Schema() {
    for (const auto &i : this->blocks) {delete i.second;}
    for (const auto &i : this->connections) {delete i.second;}
}

void Schema::save(const string &file_name) {
    ofstream out_stream;
    out_stream.open(file_name);

    out_stream << *this;
    out_stream.close();
}

void Schema::loadBlck(Block *blck) {this->blocks[blck->getID()] = blck;}

void Schema::loadConn(Connection *conn) {this->connections[conn->getID()] = conn;}

void Schema::load(const string &file_name) {
    ifstream s;
    s.open(file_name);

    s >> *this;

    s.close();
}

/* vracia ID vytvoreneho blocku */
uint32_t Schema::newBlock(func_type type, int pos_x, int pos_y) {
    static uint32_t id_count{0};
    id_count++;

    auto new_blck = new Block{id_count, pos_x, pos_y, type};
    this->blocks[id_count] = new_blck;
    return id_count;
}

uint32_t Schema::newConnection(Block *in, Block *out) {
    static uint32_t id_count{0};
    id_count++;

    /* is it possible?*/
    // TODO?

    /* add to connections vector */
    auto new_con = new Connection{id_count, in, out};
    this->connections[id_count] = new_con;

    /* tell blocks that they have new connection*/
    out->setNewInput(this->connections[id_count]);
    return id_count;
}

Block *Schema::getBlckByID(uint32_t ID) {return this->blocks[ID];}

Connection *Schema::getConByID(uint32_t ID) { return this->connections[ID];}
