
#include "schema.h"
#include "block.h"
#include "connection.h"
#include <vector>
#include <ostream>

using namespace std;

ostream &operator<<(ostream &s, const Schema &schema) {
    for (const auto &i: schema.blocks) {
        s << i;
    }
    for (const auto &i: schema.connections) {
        s << i;
    }

    return s;
}

void Schema::newBlock(blck_type type, int pos_x, int pos_y) {
    this->blocks.emplace_back(Block{pos_x, pos_y, type});
}

void Schema::newConnection(Block *in, Block *out) {
    /* is it possible?*/
    //TODO

    /* add to connections vector */
    this->connections.emplace_back(Connection{in, out});

    /* tell blocks that they have new connection*/
    out->setNewInput(&this->connections.back());

}

Block *Schema::getBlckByID(uint32_t ID) {
    Block *possible = &this->blocks[ID];
    if (possible->getID() == ID) {
        return possible;
    } else {    //TODO nefunguje
        //prejdi linearne
//        for (auto& i : this->blocks) {
//            if (i.getID() == ID) {
//                return &i;
//            }
//        }
        return nullptr;
    }
}

Schema::Schema() {
    this->blocks = vector<Block>{};
    this->connections = vector<Connection>{};
}

int main(int argc, char **argv) {

    Schema a{};
    a.newBlock(ADD);
    a.newBlock(SUB);
    a.newConnection(a.getBlckByID(0), a.getBlckByID(1));
    cout << a;

    return 0;
}