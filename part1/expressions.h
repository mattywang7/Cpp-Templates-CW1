//
// Created by Matty Wang on 11/03/2021.
//

#ifndef TEMPLATES_EXPRESSIONS_H
#define TEMPLATES_EXPRESSIONS_H

#endif //TEMPLATES_EXPRESSIONS_H

#include <iostream>

using namespace std;

// Each class has an inline function `int eval(int x)`

template<class T>
class Expression {
public:
    static inline int eval(int x) {
        return T::eval(x);
    }
};

template<int N>
class Literal {
public:
    static inline int eval(int x) {
        return N;
    }
};

class Variable {
public:
    static inline int eval(int x) {
        return x;
    }
};

// Catch division by zero exception
class DivideByZeroException : public exception {
    const char *what() const noexcept override {
        return "Division by zero is illegal.";
    }
};

template<class A, class B>
class Add {
public:
    static inline int eval(int x) {
        return A::eval(x) + B::eval(x);
    }
};

template<class A, class B>
class Minus {
public:
    static inline int eval(int x) {
        return A::eval(x) - B::eval(x);
    }
};

template<class A, class B>
class Times {
public:
    static inline int eval(int x) {
        return A::eval(x) * B::eval(x);
    }
};

template<class A, class B>
class Divide {
public:
    static inline int eval(int x) {
        if (B::eval(x) == 0) {
            throw DivideByZeroException();
        } else {
            return A::eval(x) / B::eval(x);
        }
    }
};