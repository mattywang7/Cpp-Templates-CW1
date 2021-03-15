#include <iostream>
#include "expressions.h"

const int variable = 10;

// Add Test
typedef Add<Variable, Literal<10>> expressionAdd;

// Minus Test
typedef Minus<Variable, Literal<10>> expressionMinus;

// Times Test
typedef Times<Variable, Literal<10>> expressionTimes;

// Divide Test
typedef Divide<Variable, Literal<10>> expressionDivide;

// x + (x - 2) * (x - 3)
typedef Add<Variable, Times<Minus<Variable, Literal<2>>, Minus<Variable, Literal<3>>>> expression;

// DivideByZero Test
typedef Divide<Variable, Literal<0>> expressionDivideByZero;



int main() {
    cout << "Add Test: (10 + 10) = " << expressionAdd::eval(variable) << endl;
    cout << "Minus Test: (10 - 10) = " << expressionMinus::eval(variable) << endl;
    cout << "Times Test: (10 * 10) = " << expressionTimes::eval(variable) << endl;
    cout << "Divide Test: (10 / 10) = " << expressionDivide::eval(variable) << endl;
    cout << "10 + (10 - 2) * (10 - 3) = " << expression::eval(variable) << endl;

    cout << "Divide by Zero Test: (10 / 0) = " << expressionDivideByZero::eval(variable) << endl;
    return 0;
}