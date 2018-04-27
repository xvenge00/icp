#include "block.h"

using std::vector;

Block::Block(uint32_t ID, int pos_x, int pos_y, func_type f_type) {
    this->ID = ID;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->f_type = f_type;
    this->input = vector<Connection *>{};
    this->output = {};

    // TODO ukazatel na funkciu vypoctu
}

void Block::setPos(int pos_x, int pos_y) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

uint32_t Block::getID() { return this->ID; }

double Block::getValue() { return this->output; }

bool Block::setNewInput(Connection *con) {
    // TODO checks
    this->input.emplace_back(con);

    return true;
}

