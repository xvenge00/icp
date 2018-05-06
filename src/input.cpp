#include <fstream>
#include <iostream>
#include <string>
#include <QPointF>
#include "block.h"
#include "block_graphics_object.h"
#include "connection_graphics_object.h"
#include "schema.h"
#include "schema_area.h"

// TODO tlaci sa iny format
Block *parseBlockAdd(std::ifstream &s) {
    unsigned int ID{};
    int pos_x{};
    int pos_y{};
    unsigned int in_size{};
    std::string dump;

    s >> dump >> ID >> dump >> pos_x >> dump >> pos_y >> dump >> in_size;
    getline(s, dump); // erase '\n'
    getline(s, dump); // erase '{'

    auto new_blck = new BlockAdd{ID, in_size};
    return new_blck;
}



Block *parseBlockMul(std::ifstream &s) {
    unsigned int ID{};
    int pos_x{};
    int pos_y{};
    unsigned int in_size{};
    std::string dump;

    s >> dump >> ID >> dump >> pos_x >> dump >> pos_y >> dump >> in_size;
    getline(s, dump); // erase '\n'
    getline(s, dump); // erase '{'

    auto new_blck = new BlockMul{ID, in_size};
    return new_blck;
}

Block *parseBlockSub(std::ifstream &s) {
    unsigned int ID{};
    int pos_x{};
    int pos_y{};
    std::string dump;

    s >> dump >> ID >> dump >> pos_x >> dump >> pos_y;
    getline(s, dump); // erase '\n'
    getline(s, dump); // erase '{'

    auto new_blck = new BlockSub{ID};
    return new_blck;
}

Block *parseBlockDiv(std::ifstream &s) {
    //    TODO
    return nullptr;
}

Block *parseBlockOut(std::ifstream &s) {
    unsigned int ID{};
    int pos_x{};
    int pos_y{};
    double output;
    std::string dump;

    s >> dump >> ID >> dump >> pos_x >> dump >> pos_y >> dump >> output;
    getline(s, dump); // erase '\n'
    getline(s, dump); // erase '{'

    auto new_blck = new BlockOut{ID, output};
    return new_blck;
}

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

    if (g_in != nullptr && g_out != nullptr){
        return new ConnectionGraphicsObject(g_in, g_out, new_conn);
    } else {
        return nullptr;
    }
}

//std::istream &operator>>(std::ifstream &s, Schema &b) {
//    std::string line;
//    Block *new_blck;
//    Connection *new_conn;
//
//    while (getline(s, line)) {
//        if (line == "Block ADD: {") {
//            new_blck = parseBlockAdd(s);
//            b.loadBlck(new_blck);
//        } else if (line == "Block MUL: {") {
//            new_blck = parseBlockMul(s);
//            b.loadBlck(new_blck);
//        } else if (line == "Block SUB: {") {
//            new_blck = parseBlockSub(s);
//            b.loadBlck(new_blck);
//        } else if (line == "Block DIV: {") {
//            new_blck = parseBlockDiv(s);
//            b.loadBlck(new_blck);
//        } else if (line == "Block OUT: {") {
//            new_blck = parseBlockOut(s);
//            b.loadBlck(new_blck);
//        } else if (line == "Connection: {") {
//            new_conn = parseConn(s, b);
//            b.loadConn(new_conn);
//        } else {
//            std::cerr << "Demaged file!\n";
//        }
//    }
//
//    return s;
//}
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

    s >> dump >> width
      >> dump >> height
      >> dump >> pos_x
      >> dump >> pos_y
      >> dump >> ID
      >> dump >> type_alias;

    type = static_cast<blck_type >(type_alias);
    switch (type) {
        case DIV:
            block = schema.newDivBlock();
            break;
        case SUB:
            block = schema.newSubBlock();
            break;
        case POW:
            block = schema.newPowBlock();
            break;
        case NEG:
            block = schema.newNegBlock();
            break;
        case ADD:
            block = schema.newAddBlock(input_size);
            break;
        case MUL:
            block = schema.newMulBlock(input_size);
            break;
        case OUT:
            block = schema.newOutBlock(output);
            break;
        default:
            return nullptr;
    }

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
