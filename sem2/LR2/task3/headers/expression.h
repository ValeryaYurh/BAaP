#pragma once
class Expression{
public:
    virtual ~Expression(){};
    virtual double evaluate() =0;
};