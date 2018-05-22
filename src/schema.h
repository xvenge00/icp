/**
 * @file schema.h
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 *
 * File containing the representation of schema
 */

#ifndef ICP_SCHEMA_H
#define ICP_SCHEMA_H

#include <map>

#include "block.h"
#include "connection.h"

using namespace std;

/**
 * Internal representation of schema, contains blocks and connections.
 */
class Schema {
    std::map<int, Block *> blocks;
    std::map<int, Connection *> connections;
    unsigned int block_id_gen;
    unsigned int conn_id_gen;

    std::list<Block *> to_calculate;

    void loadBlck(Block *blck);

    void loadConn(Connection *conn);

    void unset();

  public:
    Schema();

    ~Schema();

    void clear();

    BlockAdd *newAddBlock(unsigned int in_size = DEFAULT_ADD_INPUT_SIZE);
    BlockMul *newMulBlock(unsigned int in_size = DEFAULT_MUL_INPUT_SIZE);
    BlockSub *newSubBlock();
    BlockDiv *newDivBlock();
    BlockPow *newPowBlock();
    BlockNeg *newNegBlock();
    BlockOut *newOutBlock(double output);

    bool deleteBlock(Block *b);

    Connection *newConnection(Block *in, Block *out, unsigned int pos);

    /**
     * Create new connection between two blocks
     * @param in output block - input to connection
     * @param out input block - output to connection
     */
    Connection *newConnection(Block *in, Block *out);
    bool deleteConnection(Connection *conn);

    Block *getBlckByID(unsigned int ID);

    Connection *getConByID(unsigned int ID);

    /**
     * Calculate the value of blocks in schema
     * @return True if computation is successfull, otherwise false.
     */
    bool beforeCalc();
    bool compute();
    bool step();

    /**
     * Reset the schema to initial state
     */
    void clearSchema();

    void addBlock(Block *blck);

    void addConnection(Connection *conn);

    friend ostream &operator<<(ostream &s, const Schema &schema);

    friend std::istream &operator>>(std::ifstream &s, Schema &b);
};

#endif // ICP_SCHEMA_H
