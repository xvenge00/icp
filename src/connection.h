/**
 * @file connection.h
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 *
 * File containing internal data representation of connection.
 */

#ifndef ICP_CONNECTION_H
#define ICP_CONNECTION_H

#include <iostream>

/* we need to know that Block exists
 * else cyclic dependency */
class Block;

/**
 * Internal representation of connection, contains input, output, value, type,...
 */
class Connection {
    unsigned int ID;
    Block *input;
    Block *output;
    unsigned int index; // index v blocku output

  public:
    Connection(unsigned int ID, Block *input, Block *output, unsigned int index);

    unsigned int getID();

    /**
     * Get the output value of the block connected to.
     * @return Output value.
     */
    double getValue();

    Block *getOutBlock();

    unsigned int getIdx();

    Block *getInput();

    /**
     * Checks if value in input block is valid.
     * @return True if valid.
     */
    bool isInputSet();

    friend std::ostream &operator<<(std::ostream &s, const Connection &c);
};

#endif // ICP_CONNECTION_H
