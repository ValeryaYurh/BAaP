#pragma once
#include "expression.h"
class BinaryOperation : public Expression
{
    Expression* e1;
    Expression* e2;
    char op;
public:
    BinaryOperation(Expression* l, char o, Expression* r): e1(l), e2(r), op(o){};
    ~BinaryOperation() override{
        delete e1;
        delete e2;
    };
    double evaluate() override{
        double l=e1->evaluate();
        double r=e2->evaluate();
        switch (op)
        {
        case '+':
            return l+r;
        case '-':
            return l-r;
        case '*':
            return l*r;
        case '/':
            return l/r;
        default:
            return 0.0;
        }
    }
};

