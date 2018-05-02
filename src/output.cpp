#include <iostream>

#include "block.h"
#include "connection.h"
#include "schema.h"

/*
 * cela schema
 */
std::ostream &operator<<(std::ostream &s, const Schema &schema) {
    for (const auto &i : schema.blocks) {
        s << *i.second;
    }
    for (const auto &i : schema.connections) {
        s << *i.second;
    }

    return s;
}

/*
 * example out:
 * Block: {
 * 	  ID: 0
 *	  pos_x: 1
 *	  pos_y: 1
 *	  in_size: 3
 *	  type: 0
 *	  output: 13
 *}
 */
std::ostream &operator<<(std::ostream &s, const Block &b) {
    switch (b.block_type) {
    case ADD:
        return s << "Block ADD: {\n"
                 << "\tID: " << b.ID << "\n"
                 << "\tpos_x: " << b.pos_x << "\n"
                 << "\tpos_y: " << b.pos_y << "\n"
                 << "\tin_size: " << b.input_size << "\n"
                 << "}\n";
    case MUL:
        return s << "Block MUL: {\n"
                 << "\tID: " << b.ID << "\n"
                 << "\tpos_x: " << b.pos_x << "\n"
                 << "\tpos_y: " << b.pos_y << "\n"
                 << "\tin_size: " << b.input_size << "\n"
                 << "}\n";
    case SUB:
        return s << "Block SUB: {\n"
                 << "\tID: " << b.ID << "\n"
                 << "\tpos_x: " << b.pos_x << "\n"
                 << "\tpos_y: " << b.pos_y << "\n"
                 << "}\n";
    case DIV:
        return s << "Neni implementovane\n";
    case OUT:
        return s << "Block OUT: {\n"
                 << "\tID: " << b.ID << "\n"
                 << "\tpos_x: " << b.pos_x << "\n"
                 << "\tpos_y: " << b.pos_y << "\n"
                 << "\toutput: " << b.output << "\n"
                 << "}\n";
    default:
        return s << "Block: {\n"
                 << "\tID: " << b.ID << "\n"
                 << "\tpos_x: " << b.pos_x << "\n"
                 << "\tpos_y: " << b.pos_y << "\n"
                 << "\tin_size: " << b.input_size << "\n"
                 << "\ttype: " << b.block_type << "\n"
                 << "\toutput: " << b.output << "\n" //TODO otestuj na NaN
                 << "}\n";
    }
}

std::ostream &operator<<(std::ostream &s, const BlockMul &b) {
    return s << "BlockMul";
}

/*
 * Used in Schema output.
 * out example:
 * Connection: {
 *      in: 0
 *      out: 1
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
