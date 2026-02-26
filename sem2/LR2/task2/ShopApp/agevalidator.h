#ifndef AGEVALIDATOR_H
#define AGEVALIDATOR_H

#include <QString>

class AgeValidator
{
public:
    static bool validate(const QString& input, QString& errorMessage);
};

#endif
