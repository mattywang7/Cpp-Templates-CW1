//
// Created by Matty Wang on 12/03/2021.
//

#ifndef TEMPLATES_EXPRESSIONS_H
#define TEMPLATES_EXPRESSIONS_H

#endif //TEMPLATES_EXPRESSIONS_H

#include <iostream>

using namespace std;

int position = 0;

class OutOfRangeException : public exception {
    const char *what() const noexcept override {
        return "The input is not in the specified range.";
    }
};

class DivideByZeroException : public exception {
    const char *what() const noexcept override {
        return "Division by zero is illegal.";
    }
};

template<int LOWER, int UPPER>
class Bounds {
public:
    enum {
        lowerBound = LOWER,
        upperBound = UPPER
    };
};

template<int N>
class Literal {
public:
    static inline int eval(int variables[]) {
        return N;
    }

    enum {
        lowerBound = N,
        upperBound = N
    };
};

template<class T>
class Variable {
public:
    static inline int eval(int variables[]) {
        if (variables[position] < lowerBound || variables[position] > upperBound) {
            throw OutOfRangeException();
        } else {
            return variables[position++];
        }
    }

    enum {
        lowerBound = T::lowerBound,
        upperBound = T::upperBound
    };
};

template<class A, class B>
class Add {
public:
    static inline int eval(int variables[]) {
        return A::eval(variables) + B::eval(variables);
    }

    enum {
        lowerBound = A::lowerBound + B::lowerBound,
        upperBound = A::upperBound + B::upperBound
    };
};

template<class A, class B>
class Minus {
public:
    static inline int eval(int variables[]) {
        return A::eval(variables) - B::eval(variables);
    }

    enum {
        lowerBound = A::lowerBound - B::upperBound,
        upperBound = A::upperBound - B::lowerBound
    };
};

// Helper functions for Times and Divide

template<int A, int B>
struct Min {
    enum {
        value = ((A < B) ? A : B)
    };
};

template<int A, int B>
struct Max {
    enum {
        value = ((A > B) ? A : B)
    };
};

template<class A, class B>
class Times {
public:
    static inline int eval(int variables[]) {
        return A::eval(variables) * B::eval(variables);
    }

    enum {
        lowerBound = Min<Min<A::lowerBound * B::lowerBound, A::lowerBound * B::upperBound>::value, Min<A::upperBound * B::lowerBound, A::upperBound * B::upperBound>::value>::value,
        upperBound = Max<Max<A::lowerBound * B::lowerBound, A::lowerBound * B::upperBound>::value, Max<A::upperBound * B::lowerBound, A::upperBound * B::upperBound>::value>::value
    };
};

template<class A, class B>
class Divide {
public:
    static inline int eval(int variables[]) {
        if (B::eval(variables) == 0) {
            throw DivideByZeroException();
        } else {
            return A::eval(variables) / B::eval(variables);
        }
    }

    enum {
        lowerBound = Min<Min<A::lowerBound / B::lowerBound, A::lowerBound / B::upperBound>::value, Min<A::upperBound / B::lowerBound, A::upperBound / B::upperBound>::value>::value,
        upperBound = Max<Max<A::lowerBound / B::lowerBound, A::lowerBound / B::upperBound>::value, Max<A::upperBound / B::lowerBound, A::upperBound / B::upperBound>::value>::value
    };
};

// Each time call PrintBounds, the position will be reset to 0.
template<class T>
class PrintBounds {
public:
    static inline int eval(int variables[]) {
        position = 0;
        cout << T::lowerBound << " <= " << "The expression" << " <= " << T::upperBound << endl;
        return T::eval(variables);
    }

    enum {
        lowerBound = T::lowerBound,
        upperBound = T::upperBound
    };
};