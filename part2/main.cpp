#include <iostream>
#include "expressions.h"

const int variable = 3;
const int outOfRange = 10;
const int lowerBound = 0;
const int upperBound = 5;

// Add Test
typedef PrintBounds<Add<Variable<Bound<lowerBound, upperBound>>, Literal<2>>> expressionAdd;

// Minus Test
typedef PrintBounds<Minus<Variable<Bound<lowerBound, upperBound>>, Literal<2>>> expressionMinus;

// Times Test
typedef PrintBounds<Times<Variable<Bound<lowerBound, upperBound>>, Literal<2>>> expressionTimes;

// Divide Test
typedef PrintBounds<Divide<Variable<Bound<lowerBound, upperBound>>, Literal<2>>> expressionDivide;

// (x + 3) * (x + 5)
typedef PrintBounds<Times<Add<Variable<Bound<lowerBound, upperBound>>, Literal<3>>, Add<Variable<Bound<lowerBound, upperBound>>, Literal<5>>>> expression;

// OutOfRangeException Test
typedef Variable<Bound<lowerBound, upperBound>> expressionOutOfRange;

int main() {
    cout << "Add Test:" << endl << expressionAdd::eval(variable) << endl << "------------" << endl;
    cout << "Minus Test:" << endl << expressionMinus::eval(variable) << endl << "------------" << endl;
    cout << "Times Test:" << endl << expressionTimes::eval(variable) << endl << "------------" << endl;
    cout << "Divide Test:" << endl << expressionDivide::eval(variable) << endl << "------------" << endl;
    cout << "(x_{0,5} + 3) * (x_{0,5} + 5): " << endl << expression::eval(variable) << endl << "------------" << endl;

    cout << "Input x: 10 for range [0, 5]" << endl << expressionOutOfRange::eval(outOfRange) << endl;
}