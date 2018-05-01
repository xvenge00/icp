#ifndef ICP_BLOCK_H
#define ICP_BLOCK_H

#include "connection.h"
#include <iostream>
#include <vector>

const uint8_t MAX_INPUT = 10;

const uint8_t DEFAULT_ADD_INPUT_SIZE = 2;
const uint8_t DEFAULT_MUL_INPUT_SIZE = 2;

enum blck_type : int {
    ADD, SUB, MUL, DIV, OUT
};

class Block {
protected:
    uint32_t ID;
    int pos_x;
    int pos_y;
    uint8_t input_size;
    Connection *input[MAX_INPUT];
    bool out_set;     //weather the output was already set
    double output;
    blck_type block_type;

    virtual double compute(std::vector<double> &params);

public:
    Block(uint32_t ID, int pos_x, int pos_y, blck_type f_type, uint8_t input_size = 2);

    void setPos(int pos_x, int pos_y);

    uint32_t getID();

    double getValue();

    blck_type getType();

    bool setNewInput(Connection *con, uint8_t pos);

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
    BlockOut(uint32_t ID, int pos_x, int pos_y, double output);

    bool tryCompute() override;

//    void changeOutput(double output);   //neviem ci to bude fungovat, asi nie
};



class BlockAdd : public Block {
protected:
    double compute(std::vector<double> &params) override;

public:
    BlockAdd(uint32_t ID, int pos_x, int pos_y, uint8_t input_size = DEFAULT_ADD_INPUT_SIZE);
};



class BlockMul : public Block {
protected:
    double compute(std::vector<double> &params) override;

public:
    BlockMul(uint32_t ID, int pos_x, int pos_y, uint8_t input_size = DEFAULT_MUL_INPUT_SIZE);
};



class BlockSub : public Block {
protected:
    double compute(std::vector<double> &params) override;

public:
    BlockSub(uint32_t ID, int pos_x, int pos_y);
};

#endif // ICP_BLOCK_H
