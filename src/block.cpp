#include "block.h"

using std::vector;

Block::Block(unsigned int ID, int pos_x, int pos_y, blck_type f_type,unsigned int  input_size) {
    this->ID = ID;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->output = {};
    this->out_set = false;
    this->block_type = f_type;

    for (int i = 0; i < MAX_IN_SIZE; i++) { this->input[i] = nullptr; } //TODO

    /* input orez na 0-MAX_IN_SIZE */
    input_size = input_size > MAX_IN_SIZE ? MAX_IN_SIZE : input_size;
    this->input_size = input_size;
}

void Block::setPos(int pos_x, int pos_y) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

unsigned int  Block::getID() { return this->ID; }

double Block::getValue() { return this->output; }

blck_type Block::getType() { return this->block_type; }

bool Block::isSet() { return this->out_set; }

double Block::compute(std::vector<double> &params) { return 0; }

bool Block::tryCompute() {
    vector<double> in_values{};
    double value;

    //najprv skontroluj ci je nejaky co ma input not set
    for (int i = 0; i < this->input_size; i++) {
        if (this->input[i] != nullptr && !this->input[i]->isInputSet()) {
            return false;
        }
    }

    for (int i = 0; i < this->input_size; i++) {
        if (this->input[i] == nullptr) {
            std::cout << "Zadajte vstupnú hodnotu pre " << i + 1 << ". vstup: ";
            std::cin >> value;

//            //vytvor virtualny out block
//            BlockOut virt_block = BlockOut{0, 0, 0, value};
//            Connection virt_conn = Connection{};

            in_values.push_back(value);
        }     //TODO vytvorenie virt blocku
        else {
            value = this->input[i]->getValue();
            in_values.push_back(value);
        }

    }

    //TODO
//    /* if all inputs are set */
//    for (const auto &i : this->input) {
//        if (!i->isInputSet()) {
//            return false;
//        }
//        in_values.push_back(i->getValue());
//    }
//
//    /* if not all inputs are connected */
//    for (unsigned long i = in_values.size(); i < this->input_size; i++) {
//        double value;
//
//        std::cout << "Zadajte vstupnú hodnotu pre " << i + 1 << ". vstup: ";
//        std::cin >> value;
//
//        in_values.push_back(value);
//    }

    /* inputs are set, we can compute */
    this->output = this->compute(in_values);
    this->out_set = true;

    return true;
}

bool Block::setNewInput(Connection *con, unsigned int  pos) {
    if (pos < this->input_size) {
        this->input[pos] = con;
        return true;
    } else {
        return false;
    }
}

bool Block::unsetInput(unsigned int pos) {
    if (pos < this->input_size) {
        this->input[pos] = nullptr;
        return true;
    } else {
        return false;
    }
}

BlockOut::BlockOut(unsigned int ID, int pos_x, int pos_y, double output) : Block(ID, pos_x, pos_y, OUT, 0) {
    this->output = output;
    this->out_set = true;
}

bool BlockOut::tryCompute() {
    return true;
}

BlockAdd::BlockAdd(unsigned int ID, int pos_x, int pos_y, unsigned int input_size) : Block(ID, pos_x, pos_y, ADD, input_size) {
    /* input orez na 2-MAX_IN_SIZE */
    if (input_size < 2) { this->input_size = 2; }
}

double BlockAdd::compute(std::vector<double> &params) {
    double acc{0};
    for (const auto &i : params) {
        acc += i;
    }

    return acc;
}

BlockMul::BlockMul(unsigned int ID, int pos_x, int pos_y,unsigned int input_size) : Block(ID, pos_x, pos_y, MUL, input_size) {
    /* input orez na 2-MAX_IN_SIZE */
    if (input_size < 2) { this->input_size = 2; }
}

double BlockMul::compute(std::vector<double> &params) {
    double acc{1};
    for (const auto &i : params) {
        acc *= i;
    }

    return acc;
}

BlockSub::BlockSub(unsigned int ID, int pos_x, int pos_y) : Block(ID, pos_x, pos_y, SUB) {}

double BlockSub::compute(std::vector<double> &params) { return params[0] - params[1]; }
