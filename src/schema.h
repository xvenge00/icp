#ifndef ICP_SCHEMA_H
#define ICP_SCHEMA_H

#include <vector>

#include "block.h"
#include "connection.h"

using namespace std;

class Schema {
    vector<Block> blocks; // TODO co tak hash table a ID bude kluc??
    vector<Connection> connections;

  public:
    Schema();

    void save(const string &file_name);

    void newBlock(blck_type type, int pos_x = 1, int pos_y = 1);

    void newConnection(Block *in, Block *out);

    Block *getBlckByID(uint32_t ID);

    friend ostream &operator<<(ostream &s, const Schema &schema);
};

#endif // ICP_SCHEMA_H
