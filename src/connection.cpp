
#include "connection.h"
#include "block.h"

using namespace std;

//Must be checked if is set before getting value
double Connection::getValue() { return this->input->getValue(); }

uint32_t Connection::getID() { return this->ID; }

bool Connection::isInputSet() { return this->input->isSet(); }

Connection::Connection(uint32_t ID, Block *input, Block *output) {
    this->ID = ID;
    this->input = input;
    this->output = output;
}
