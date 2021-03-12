#include <iostream>
#include "expressions.h"

// x + (y - 2) * (z - 3)

// input arrays
int variables_1[3] = {3, 13, 23};
int variables_2[3] = {5, 15, 25};
int variables_3[3] = {7, 17, 27};

// bounds for each variable
const int lower_bound_1 = 0;
const int upper_bound_1 = 9;
const int lower_bound_2 = 10;
const int upper_bound_2 = 19;
const int lower_bound_3 = 20;
const int upper_bound_3 = 29;

typedef PrintBounds<Add<Variable<Bounds<lower_bound_1, upper_bound_1>>,
                        Times<Minus<Variable<Bounds<lower_bound_2, upper_bound_2>>, Literal<2>>,
                              Minus<Variable<Bounds<lower_bound_3, upper_bound_3>>, Literal<3>>>>> expression;

int main() {
    int outputs[3];
    outputs[0] = expression::eval(variables_1);
    outputs[1] = expression::eval(variables_2);
    outputs[2] = expression::eval(variables_3);
    for (auto output : outputs) {
        cout << output << endl;
    }

    // Test OutOfRangeException
    variables_2[1] = 21; // y is out of range now
    cout << expression::eval(variables_2) << endl;
    return 0;
}