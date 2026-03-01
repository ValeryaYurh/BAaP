#pragma once
#include "expression.h"
class Number: public Expression{
    double value;
public:
    Number(double v):value(v){};
    double evaluate() override{
        return value;
    } ;

};