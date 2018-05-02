
#ifndef ICP_CONNECTION_H
#define ICP_CONNECTION_H

#include <iostream>

/* we need to know that Block exists
 * else cyclic dependency */
class Block;

class Connection {
    unsigned int ID;
    Block *input;
    Block *output;
    unsigned int index; //index v blocku output

  public:
    Connection(unsigned int ID, Block *input, Block *output, unsigned int index);

    unsigned int getID();

    double getValue();

    Block *getOutBlock();

    unsigned int getIdx();

    Block *getInput();

    bool isInputSet();

    friend std::ostream &operator<<(std::ostream &s, const Connection &c);
};

#endif // ICP_CONNECTION_H
