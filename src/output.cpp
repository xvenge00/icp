#include <iostream>

#include "block.h"
#include "connection.h"
#include "schema.h"

/*
 * cela schema
 */
std::ostream &operator<<(std::ostream &s, const Schema &schema) {
    for (const auto &i : schema.blocks) {s << *i.second;}
    for (const auto &i : schema.connections) {s << *i.second;}
    s << "\n";

    return s;
}

/*
 * example out:
 * [1,2]
 */
std::ostream &operator<<(std::ostream &s,
                         const std::vector<Connection *> vect) {
    for (const auto &i : vect) {s << "[" << i << "]";}
    return s;
}

/*
 * example out:
 * Block: {
 * 	  ID: 0
 *	  pos_x: 1
 *	  pos_y: 1
 *	  type: 0
 *}
 */
std::ostream &operator<<(std::ostream &s, const Block &b) {
    return s << "Block: {\n"
             << "\tID: " << b.ID << "\n"
             << "\tpos_x: " << b.pos_x << "\n"
             << "\tpos_y: " << b.pos_y << "\n"
             << "\ttype: " << b.f_type << "\n"
             << "}\n";
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
      << "}";
    return s;
}
