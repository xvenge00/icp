#ifndef ICP_SCHEMA_H
#define ICP_SCHEMA_H

#include <map>

#include "block.h"
#include "connection.h"

using namespace std;

class Schema {
    std::map<int, Block *> blocks;
    std::map<int, Connection *> connections;
    unsigned int block_id_gen;
    unsigned int conn_id_gen;

    void loadBlck(Block *blck);

    void loadConn(Connection *conn);

  public:
    Schema();

    ~Schema();

    BlockAdd *newAddBlock(unsigned int in_size = DEFAULT_ADD_INPUT_SIZE);
    BlockMul *newMulBlock(unsigned int in_size = DEFAULT_MUL_INPUT_SIZE);
    BlockSub *newSubBlock();
    //    unsigned int newDivBlock();   //TODO
    BlockOut *newOutBlock(double output);

    bool deleteBlock(Block *b);

    Connection *newConnection(Block *in, Block *out, unsigned int pos);
    Connection *newConnection(Block *in, Block *out);
    bool deleteConnection(Connection *conn);

    Block *getBlckByID(unsigned int ID);

    Connection *getConByID(unsigned int ID);

    /* On success returns true */
    bool compute();

    void addBlock(Block *blck);

    friend ostream &operator<<(ostream &s, const Schema &schema);

    friend std::istream &operator>>(std::ifstream &s, Schema &b);
};

#endif // ICP_SCHEMA_H
