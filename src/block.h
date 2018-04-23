
#ifndef ICP_BLOCK_H
#define ICP_BLOCK_H

#include <iostream>
#include <vector>
#include "connection.h"

enum blck_type : int {
    ADD,
    SUB,
    CUSTOM
};

//class Block;
//std::ostream& operator<< (std::ostream& s, const Block& b);
//int Block::getID();

class Block {
    uint32_t ID;
    int pos_x;
    int pos_y;
    blck_type type;
    std::vector<Connection *> input;
//    std::vector<Connection *> output;
    double output;
//    Computable *op;

public:
    Block(int pos_x, int pos_y, blck_type type);

    void setPos(int pos_x, int pos_y);

    uint32_t getID();

    bool setNewInput(Connection *con);

    double getValue();

    friend std::istream &operator>>(std::istream &s, Block &b);

    friend std::ostream &operator<<(std::ostream &s, const Block &b);
};

#endif //ICP_BLOCK_H
