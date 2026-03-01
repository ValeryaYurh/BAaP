#include "headers/expression.h"
#include "headers/binaryOperation.h"
#include "headers/number.h"
#include <iostream>
int main(int argc, char const *argv[])
{
    Expression *sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
    Expression *expr = new BinaryOperation(new Number(3), '+', sube);
    std::cout << expr->evaluate() << std::endl;

    delete expr;
    return 0;
}
