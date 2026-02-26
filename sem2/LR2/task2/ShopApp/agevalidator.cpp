#include "agevalidator.h"

bool AgeValidator::validate(const QString& input, QString& errorMessage)
{
    QString trimmed = input.trimmed();
    if(trimmed.isEmpty()) { errorMessage = "Введите возраст"; return false; }

    bool ok;
    int age = trimmed.toInt(&ok);
    if(!ok) { errorMessage = "Некорректный формат"; return false; }

    if(age < 0 || age > 130) { errorMessage = "Возраст вне диапазона (0-130)"; return false; }

    return true;
}
