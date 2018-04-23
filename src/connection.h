
#ifndef ICP_CONNECTION_H
#define ICP_CONNECTION_H

#include <iostream>

/* we need to know that Block exists
 * else cyclic dependency */
class Block;

class Connection {
    uint32_t ID;
    Block *input;
    Block *output;

public:
    Connection(Block *input, Block *output);

    double getValue();

    friend std::ostream &operator<<(std::ostream &s, const Connection *c);

    friend std::ostream &operator<<(std::ostream &s, const Connection &c);
};

#endif //ICP_CONNECTION_H