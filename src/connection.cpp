
#include "connection.h"
#include "block.h"

using namespace std;

// Must be checked if is set before getting value
double Connection::getValue() { return this->input->getValue(); }

unsigned int Connection::getID() { return this->ID; }

bool Connection::isInputSet() { return this->input->isSet(); }

Block *Connection::getOutBlock() { return this->output; }

unsigned int Connection::getIdx() { return this->index; }

Block *Connection::getInput() { return this->input; }

Connection::Connection(unsigned int ID, Block *input, Block *output,
                       unsigned int index) {
    this->ID = ID;
    this->input = input;
    this->output = output;
    this->index = index;
}
