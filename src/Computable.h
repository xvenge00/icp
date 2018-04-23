//
// Created by adam on 4/22/18.
//

#ifndef ICP_COMPUTABLE_H
#define ICP_COMPUTABLE_H

#include <vector>

class Computable {
public:
    static double add(std::vector<double> &params);

    static double sub(std::vector<double> &params);

    static double custom(std::vector<double> &params);
};

#endif //ICP_COMPUTABLE_H
