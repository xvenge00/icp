
#include "connection.h"
#include "block.h"

using namespace std;

double Connection::getValue() { return this->input->getValue(); }

uint32_t Connection::getID() { return this->ID;}

Connection::Connection(uint32_t ID, Block *input, Block *output) {
    this->ID = ID;
    this->input = input;
    this->output = output;
}
