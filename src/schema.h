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

  public:
    Schema();

    ~Schema();

    /** Set output of all Blocks as invalid. */
    void unset();

    /** Deletes all Blocks and Connections in Schema. */
    void clear();

    /** Creates and adds new AddBlock
     * @param in_size input size
     * @return pointer to created Block
     */
    BlockAdd *newAddBlock(unsigned int in_size = DEFAULT_ADD_INPUT_SIZE);

    /** Creates and adds new MulBlock
     * @param in_size input size
     * @return pointer to created Block
     */
    BlockMul *newMulBlock(unsigned int in_size = DEFAULT_MUL_INPUT_SIZE);

    /** Creates and adds new SubBlock
     * @return pointer to created Block
     */
    BlockSub *newSubBlock();

    /** Creates and adds new DivBlock
     * @return pointer to created Block
     */
    BlockDiv *newDivBlock();

    /** Creates and adds new PowBlock
     * @return pointer to created Block
     */
    BlockPow *newPowBlock();

    /** Creates and adds new NegBlock
     * @return pointer to created Block
     */
    BlockNeg *newNegBlock();

    /** Creates and adds new OutBlock
     * @return pointer to created Block
     */
    BlockOut *newOutBlock(double output);

    /**
     * Delete block and connections tied to it.
     * @param b Block to delete.
     * @return True if successful.
     */
    bool deleteBlock(Block *b);

    /**
     * Create new connection and add to schema.
     * @param in input to connection
     * @param out output to connection
     * @param pos Index of port in Output block.
     * @return Pointer to new Connection if success, else nullptr.
     */
    Connection *newConnection(Block *in, Block *out, unsigned int pos);

    /**
     * Create new connection and add to schema.
     * @param in input to connection
     * @param out output to connection
     * @return Pointer to new Connection if success, else nullptr.
     */
    Connection *newConnection(Block *in, Block *out);

    /**
     * Deletes connection from schema and from input of block.
     * @param conn pointer to connection to delete
     * @return True if success.
     */
    bool deleteConnection(Connection *conn);

    Block *getBlckByID(unsigned int ID);

    Connection *getConByID(unsigned int ID);

    /**
     * Sets vector to_calculate, unsets all blocks outputs as invalid.
     */
    bool beforeCalc();

    /**
     * Calculate the value of blocks in schema
     * @return True if computation is successfull, otherwise false.
     */
    bool compute();

    /**
     * Calculate value of first block you can.
     * @return True if success, false if no value can be calculated.
     */
    bool step();

    /**
     * Reset the schema to initial state
     */
    void clearSchema();

    /** Adds already created block to Schema.
     * @param blck block to add
     */
    void addBlock(Block *blck);

    /** Adds already created connection to Schema.
     * @param conn connection to add
     */
    void addConnection(Connection *conn);
};

#endif // ICP_SCHEMA_H
