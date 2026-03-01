#include <iostream>

class Expression {
public:
    virtual ~Expression() = default;

    // уникальный идентификатор типа
    virtual int typeId() const = 0;
};

class Number : public Expression {
public:
    int typeId() const override { return 1; }
};

class BinaryOperation : public Expression {
public:
    int typeId() const override { return 2; }
};

// сравнение
bool isSameType(const Expression* a, const Expression* b) {
    if (!a || !b) return false; // не nullptr
    return a->typeId() == b->typeId();
}

int main() {
    Number n1, n2;
    BinaryOperation op1, op2;
    std::cout << isSameType(&n1, &n2) << "\n";
    std::cout << isSameType(&n1, &op1) << "\n";
    std::cout << isSameType(&op1, &op2) << "\n";
}
