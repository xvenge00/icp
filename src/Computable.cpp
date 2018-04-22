
#include "Computable.h"
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>

using namespace std;

class Computable {
public:
    virtual double compute(vector<double> &params)=0;
};


class Add : public Computable {
public:
    double compute(vector<double> &params) override {
        double acc{0};
        for (const auto &i: params) {
            acc += i;
        }

        return acc;
    }
};

class Sub : public Computable {
public:
    double compute(vector<double> &params) override {
        double acc{0};
        for (const auto &i: params) {
            acc -= i;
        }

        return acc;
    }
};

int main(int argc, char **argv) {

    Add a{};
    vector<double> v{1, 2, 3};
    cout << a.compute(v) << "\n";

    return 0;
}