#include "block.h"
#include "schema.h"
#include <fstream>
#include <iostream>
#include <string>

//TODO tlaci sa iny format
Block *parseBlockAdd(std::ifstream &s) {
    unsigned int ID{};
    int pos_x{};
    int pos_y{};
    unsigned int in_size{};
    std::string dump;

    s >> dump >> ID >> dump >> pos_x >> dump >> pos_y >> dump >> in_size;
    getline(s, dump); // erase '\n'
    getline(s, dump); // erase '{'

    auto new_blck = new BlockAdd{ID, pos_x, pos_y, in_size};
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

    auto new_blck = new BlockMul{ID, pos_x, pos_y, in_size};
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

    auto new_blck = new BlockSub{ID, pos_x, pos_y};
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

    auto new_blck = new BlockOut{ID, pos_x, pos_y, output};
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

    ins >> dump >> ID >> dump >> in >> dump >> out >> dump >>index;
    getline(ins, dump);
    getline(ins, dump);

    input = b.getBlckByID(in);
    output = b.getBlckByID(out);
    auto new_con = new Connection{ID, input, output, index};
    output->setNewInput(new_con, index);

    return new_con;
}

std::istream &operator>>(std::ifstream &s, Schema &b) {
    std::string line;
    Block *new_blck;
    Connection *new_conn;

    while (getline(s, line)) {
        if (line == "Block ADD: {") {
            new_blck = parseBlockAdd(s);
            b.loadBlck(new_blck);
        } else if (line == "Block MUL: {") {
            new_blck = parseBlockMul(s);
            b.loadBlck(new_blck);
        } else if (line == "Block SUB: {") {
            new_blck = parseBlockSub(s);
            b.loadBlck(new_blck);
        } else if (line == "Block DIV: {") {
            new_blck = parseBlockDiv(s);
            b.loadBlck(new_blck);
        } else if (line == "Block OUT: {") {
            new_blck = parseBlockOut(s);
            b.loadBlck(new_blck);
        } else if (line == "Connection: {") {
            new_conn = parseConn(s, b);
            b.loadConn(new_conn);
        } else {
            std::cerr << "Demaged file!\n";
        }
    }

    return s;
}
