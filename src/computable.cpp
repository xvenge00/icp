#include "computable.h"

#include <limits>
#include <iostream>
#include <algorithm>

using std::vector;

double Computable::add(vector<double> &params) {
    double acc{0};
    for (const auto &i: params) {
        acc += i;
    }

    return acc;
}

double Computable::sub(vector<double> &params) {
    if (params.size() != 2) {
//            throw Something
    }
    double acc{0};
    for (const auto &i: params) {
        acc -= i;
    }

    return acc;
}

double Computable::custom(vector<double> &params) {
    //TODO
    return 0;
}

