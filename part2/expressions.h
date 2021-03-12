//
// Created by Matty Wang on 11/03/2021.
//

#ifndef TEMPLATES_EXPRESSIONS_H
#define TEMPLATES_EXPRESSIONS_H

#endif //TEMPLATES_EXPRESSIONS_H

#include <iostream>

using namespace std;

class OutOfRangeException : public exception {
    const char *what() const noexcept override {
        return "The input for x is not in the specified range.";
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
    static inline int eval(int x) {
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
    static inline int eval(int x) {
        if (x < lowerBound || x > upperBound) {
            throw OutOfRangeException();
        } else {
            return x;
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
    static inline int eval(int x) {
        return A::eval(x) + B::eval(x);
    }

    enum {
        lowerBound = A::lowerBound + B::lowerBound,
        upperBound = A::upperBound + B::upperBound
    };
};

// loA <= A <= hiA
// (loB <= B <= hiB) ------> (-hiB <= -B <= -loB)
// loA - hiB <= A - B <= hiA - loB
template<class A, class B>
class Minus {
public:
    static inline int eval(int x) {
        return A::eval(x) - B::eval(x);
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
    static inline int eval(int x) {
        return A::eval(x) * B::eval(x);
    }

    enum {
        lowerBound = Min<Min<A::lowerBound * B::lowerBound, A::lowerBound * B::upperBound>::value, Min<A::upperBound * B::lowerBound, A::upperBound * B::upperBound>::value>::value,
        upperBound = Max<Max<A::lowerBound * B::lowerBound, A::lowerBound * B::upperBound>::value, Max<A::upperBound * B::lowerBound, A::upperBound * B::upperBound>::value>::value
    };
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

    enum {
        lowerBound = Min<Min<A::lowerBound / B::lowerBound, A::lowerBound / B::upperBound>::value, Min<A::upperBound / B::lowerBound, A::upperBound / B::upperBound>::value>::value,
        upperBound = Max<Max<A::lowerBound / B::lowerBound, A::lowerBound / B::upperBound>::value, Max<A::upperBound / B::lowerBound, A::upperBound / B::upperBound>::value>::value
    };
};

template<class T>
class PrintBounds {
public:
    static inline int eval(int x) {
        cout << T::lowerBound << " <= " << "The expression" << " <= " << T::upperBound << endl;
        return T::eval(x);
    }

    enum {
        lowerBound = T::lowerBound,
        upperBound = T::upperBound
    };
};