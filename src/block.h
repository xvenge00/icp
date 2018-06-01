/**
 * @file block.h
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 *
 * File containing the definition and operation on block
 */

#ifndef ICP_BLOCK_H
#define ICP_BLOCK_H

#include "connection.h"
#include <array>
#include <iostream>
#include <vector>

const unsigned int MAX_IN_SIZE = 10;

const unsigned int DEFAULT_ADD_INPUT_SIZE = 2;
const unsigned int DEFAULT_MUL_INPUT_SIZE = 2;

enum blck_type : int { ADD, SUB, MUL, DIV, POW, NEG, OUT };

/**
 * Internal data representation of block, contains value, type,...
 */
class Block {
  protected:
    unsigned int ID;
    unsigned int input_size;
    std::array<Connection *, MAX_IN_SIZE> input;
    bool out_set; // weather the output was already set
    double output;
    blck_type block_type;

    /**
     * Block specific function.
     * @param params input values in correct order
     * @return f(params)
     */
    virtual double compute(std::vector<double> &params);

  public:
    Block(unsigned int ID, blck_type f_type, unsigned int input_size = 2);

    unsigned int getID();

    double getValue();

    void setValue(double value);

    blck_type getType();

    /**
     * @return Pointers to all input connections of a block in a vector.
     */
    std::vector<Connection *> getInputs();

    unsigned int getInputSize();

    /**
     * @return First free index. If nothing is free, then returns input_size.
     */
    unsigned getFirstFreeIdx();

    /** Adds new connection to the input.
     * @param con Pointer to Connection. Should be initialized.
     * @param pos Which input it is. Indexed from 0.
     * @return true if successful, else false
     */
    bool setNewInput(Connection *con, unsigned int pos);

    /** Deletes Connection.
     * @param pos index of input to delete
     * @return ID of deleted connection
     */
    unsigned int unsetInput(unsigned int pos);

    /**
     * If possible, compute block output, set output.
     * @return True if successful, else false.
     */
    virtual bool tryCompute();

    bool isSet();

    /**
     * Set output as not valid.
     */
    void unset();

    friend std::ostream &operator<<(std::ostream &s, const Block &b);
};

class BlockOut : public Block {
  public:
    BlockOut(unsigned int ID, double output);

    bool tryCompute() override;
};

class BlockAdd : public Block {
  protected:
    double compute(std::vector<double> &params) override;

  public:
    explicit BlockAdd(unsigned int ID, unsigned int input_size = DEFAULT_ADD_INPUT_SIZE);
};

class BlockMul : public Block {
  protected:
    double compute(std::vector<double> &params) override;

  public:
    explicit BlockMul(unsigned int ID, unsigned int input_size = DEFAULT_MUL_INPUT_SIZE);
};

class BlockSub : public Block {
  protected:
    double compute(std::vector<double> &params) override;

  public:
    explicit BlockSub(unsigned int ID);
};

class BlockDiv : public Block {
  protected:
    double compute(std::vector<double> &params) override;

  public:
    explicit BlockDiv(unsigned int ID);
};

class BlockPow : public Block {
  protected:
    double compute(std::vector<double> &params) override;

  public:
    explicit BlockPow(unsigned int ID);
};

class BlockNeg : public Block {
  protected:
    double compute(std::vector<double> &params) override;

  public:
    explicit BlockNeg(unsigned int ID);
};

#endif // ICP_BLOCK_H
