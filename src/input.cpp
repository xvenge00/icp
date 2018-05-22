/**
 * @file input.cpp
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 */

#include "block.h"
#include "block_graphics_object.h"
#include "connection_graphics_object.h"
#include "schema.h"
#include "schema_area.h"
#include <QPointF>
#include <fstream>
#include <iostream>
#include <string>

Connection *parseConn(std::ifstream &ins, Schema &b) {
    Block *input{};
    Block *output{};

    unsigned int ID{};
    unsigned int in{};
    unsigned int out{};
    unsigned int index{};
    std::string dump;

    ins >> dump >> ID >> dump >> in >> dump >> out >> dump >> index;
    getline(ins, dump);
    getline(ins, dump);

    input = b.getBlckByID(in);
    output = b.getBlckByID(out);
    auto new_con = new Connection{ID, input, output, index};
    output->setNewInput(new_con, index);

    return new_con;
}

ConnectionGraphicsObject *parseGraphicsConn(std::ifstream &s, SchemaArea &area) {
    Connection *new_conn = parseConn(s, area.schema);
    area.schema.addConnection(new_conn);

    Block *in = new_conn->getInput();
    Block *out = new_conn->getOutBlock();
    BlockGraphicsObject *g_in, *g_out;

    for (const auto &i : area.items(Qt::AscendingOrder)) {
        BlockGraphicsObject *ptr = dynamic_cast<BlockGraphicsObject *>(i);
        if (ptr != nullptr) {
            if (ptr->getBlock() == in) {
                g_in = ptr;
            } else {
                g_out = ptr;
            }
        }
    }

    if (g_in != nullptr && g_out != nullptr) {
        return new ConnectionGraphicsObject(g_in, g_out, new_conn);
    } else {
        return nullptr;
    }
}

BlockGraphicsObject *parseGraphicsBlock(std::ifstream &s, Schema &schema) {
    Block *block;
    BlockGraphicsObject *block_graphics;

    blck_type type;
    int type_alias;
    unsigned int ID{};
    double pos_x{};
    double pos_y{};
    unsigned width{};
    unsigned height{};
    double output{};
    unsigned input_size{};
    std::string dump;

    s >> dump >> width >> dump >> height >> dump >> pos_x >> dump >> pos_y >> dump >> ID >> dump >> type_alias;

    type = static_cast<blck_type>(type_alias);
    switch (type) {
    case DIV:
        block = new BlockDiv{ID};
        break;
    case SUB:
        block = new BlockSub{ID};
        break;
    case POW:
        block = new BlockPow{ID};
        break;
    case NEG:
        block = new BlockNeg{ID};
        break;
    case ADD:
        block = new BlockAdd{ID};
        break;
    case MUL:
        block = new BlockMul{ID};
        break;
    case OUT:
        block = new BlockOut{ID, output};
        break;
    default:
        return nullptr;
    }
    schema.addBlock(block);

    block_graphics = new BlockGraphicsObject(block);

    block_graphics->setPos(QPointF(pos_x, pos_y));
    return block_graphics;
}

std::istream &operator>>(std::ifstream &s, SchemaArea &area) {
    std::string line;

    while (getline(s, line)) {
        if (line == "Block {") {
            BlockGraphicsObject *new_blck = parseGraphicsBlock(s, area.schema);
            area.addItem(new_blck);
        } else if (line == "Connection: {") {
            ConnectionGraphicsObject *new_conn = parseGraphicsConn(s, area);
            area.addItem(new_conn);
        } else {
            std::cerr << "Demaged file!\n";
        }
    }

    return s;
}
