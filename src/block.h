#ifndef ICP_BLOCK_H
#define ICP_BLOCK_H

#include <iostream>
#include <vector>

#include "connection.h"

enum func_type : int { ADD, SUB, CUSTOM };

class Block {
    uint32_t ID;
    int pos_x;
    int pos_y;
    func_type f_type;
    std::vector<Connection *> input;
    double output;
    //    Computable *op;

  public:
    Block(uint32_t ID, int pos_x, int pos_y, func_type f_type);

    void setPos(int pos_x, int pos_y);

    uint32_t getID();

    bool setNewInput(Connection *con);

    double getValue();

    friend std::ostream &operator<<(std::ostream &s, const Block &b);
};

#endif // ICP_BLOCK_H
