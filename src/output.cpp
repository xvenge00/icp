#include <iostream>

#include "block.h"
#include "block_graphics_object.h"
#include "connection.h"
#include "schema.h"
#include "schema_area.h"

std::ostream &operator<<(std::ostream &s, const Block &b) {
    switch (b.block_type) {
    case ADD:
    case MUL:
        return s << "\ttype: " << b.block_type << "\n"
                 << "\tID: " << b.ID << "\n"
                 << "\tin_size: " << b.input_size;
    case SUB:
        return s << "\ttype: " << b.block_type << "\n"
                 << "\tID: " << b.ID;
    case DIV:
        return s << "Neni implementovane\n";
    case OUT:
        return s << "\ttype: " << b.block_type << "\n"
                 << "\tID: " << b.ID << "\n"
                 << "\toutput: " << b.output;
    default:
        return s << "Block: {\n"
                 << "\tID: " << b.ID << "\n"
                 << "\tin_size: " << b.input_size << "\n"
                 << "\ttype: " << b.block_type << "\n"
                 << "\toutput: " << b.output << "\n" //TODO otestuj na NaN
                 << "}\n";
    }
}

std::ostream &operator<<(std::ostream &s, const BlockGraphicsObject &b) {
    return s << "Block {\n"
             << "\tx: " << b.pos().x() << "\n"
             << "\ty: " << b.pos().y() << "\n"
             << *b._block << "\n"
             << "}\n";
}

std::ostream &operator<<(std::ostream &s, const SchemaArea &a) {
    for (const auto &i : a.items()) {
        void *casted = dynamic_cast<BlockGraphicsObject *>(i); // TODO connection
        if (casted != nullptr) {
            s << *dynamic_cast<BlockGraphicsObject *>(i);
        } else {
            s << "connection";
        }
    }
    return s;
}

std::ostream &operator<<(std::ostream &s, const BlockMul &b) { return s << "BlockMul"; }

/*
 * Used in Schema output.
 * out example:
 * Connection: {
 *      in: 0
 *      out: 1
 *      index: 2
 * }
 */
std::ostream &operator<<(std::ostream &s, const Connection &c) {
    s << "Connection: {\n"
      << "\tID: " << c.ID << "\n"
      << "\tin: " << c.input->getID() << "\n"
      << "\tout: " << c.output->getID() << "\n"
      << "\tindex: " << c.index << "\n"
      << "}\n";
    return s;
}
