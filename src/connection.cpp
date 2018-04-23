
#include "connection.h"
#include "block.h"

using namespace std;

double Connection::getValue() {
    return this->input->getValue();
}

Connection::Connection(Block *input, Block *output) {
    static uint32_t id_count{0};

    this->ID = id_count++;
    this->input = input;
    this->output = output;
}
