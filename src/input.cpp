#include <iostream>
#include <string>
#include <fstream>
#include "block.h"
#include "schema.h"

Block *parseBlock(std::ifstream &ins) {
    uint32_t ID{};
    int pos_x{};
    int pos_y{};
    func_type f_type{};
    int f_type_alias{};
    std::string dump;

    ins >> dump >> ID >> dump >> pos_x >> dump >> pos_y >> dump >> f_type_alias;
    getline(ins, dump);     // erase '\n'
    getline(ins, dump);     // erase '{'

    f_type = static_cast<func_type>(f_type_alias);

    auto new_blck = new Block{ID, pos_x, pos_y, f_type};
    return new_blck;
}

Connection *parseConn(std::ifstream &ins, Schema &b) {
    uint32_t ID{};
    uint32_t in{};
    uint32_t out{};
    std::string dump;

    ins >> dump >> ID >> dump >> in >> dump >> out;
    getline(ins, dump);
    getline(ins, dump);

    auto new_con = new Connection{ID, b.getBlckByID(in), b.getBlckByID(out)};
    return new_con;
}

std::istream &operator>>(std::ifstream &s, Schema &b) {
    std::string line;
    Block *new_blck;
    Connection *new_conn;

    while (getline(s, line)) {
        if (line == "Block: {") {
            new_blck = parseBlock(s);
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

