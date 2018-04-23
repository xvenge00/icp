
#include <array>
#include <vector>
#include <iostream>
#include "block.h"

using namespace std;

Block::Block(int pos_x, int pos_y, blck_type type) {
    static uint32_t id_count{0};

    this->ID = id_count++;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->type = type;
    this->input = vector<Connection *>{};
    this->output = {};

    //TODO ukazatel na funkciu vypoctu
}

void Block::setPos(int pos_x, int pos_y) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

uint32_t Block::getID() {
    return this->ID;
}

double Block::getValue() {
    return this->output;
}

bool Block::setNewInput(Connection *con) {
    //TODO checks
    this->input.emplace_back(con);

    return true;
}

istream &operator>>(istream &s, Block &b) {

    return s;
}

ostream &operator<<(ostream &s, const std::vector<Connection *> vect) {
    for (const auto &i: vect) {
        s << "[" << i << "]";
    }
    return s;
}

ostream &operator<<(ostream &s, const Block &b) {
    return s << "Block: {\n" <<
             "\tID: " << b.ID << "\n" <<
             "\tpos_x: " << b.pos_x << "\n" <<
             "\tpos_y: " << b.pos_y << "\n" <<
             "\ttype: " << b.type << "\n" <<
             "\tinput: " << b.input << "\n" <<
             "}\n";
}