
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

/*
 * Used inside block output
 * out example:
 * 0,1
 */
ostream &operator<<(ostream &s, const Connection *c) {
    s << (*c).input->getID() << "," << (*c).output->getID();
    return s;
}

/*
 * Used in Schema output.
 * out example:
 * Connection: {
 *      in: 0
 *      out: 1
 * }
 */
ostream &operator<<(ostream &s, const Connection &c) {
    s << "Connection: {\n" <<
      "\tID: " << c.ID << "\n" <<
      "\tin: " << c.input->getID() << "\n" <<
      "\tout: " << c.output->getID() << "\n" <<
      "}";
    return s;
}
