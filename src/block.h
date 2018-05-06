/**
 * @file block.h
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
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

class Block {
  protected:
    unsigned int ID;
    unsigned int input_size;
    std::array<Connection *, MAX_IN_SIZE> input;
    bool out_set; // weather the output was already set
    double output;
    blck_type block_type;

    virtual double compute(std::vector<double> &params);

  public:
    Block(unsigned int ID, blck_type f_type, unsigned int input_size = 2);

    unsigned int getID();

    double getValue();

    blck_type getType();

    std::vector<Connection *> getInputs();

    unsigned int getInputSize();

    /* If nothing is free, then returns input_size */
    unsigned getFirstFreeIdx();

    bool setNewInput(Connection *con, unsigned int pos);

    /* deletes Connection, returns ID of deleted CONNECTION */
    unsigned int unsetInput(unsigned int pos);

    /*
     * If possible, compute block output, set output, return true.
     * If not possible, return false.
     */
    virtual bool tryCompute();

    bool isSet();

    friend std::ostream &operator<<(std::ostream &s, const Block &b);
};

class BlockOut : public Block {
    //    virtual double compute(std::vector<double> &params) override;
  public:
    BlockOut(unsigned int ID, double output);

    bool tryCompute() override;

    //    void changeOutput(double output);   //neviem ci to bude fungovat, asi
    //    nie
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
