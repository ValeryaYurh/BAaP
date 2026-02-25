#ifndef DATE_H
#define DATE_H

#include <string>

class Date
{
public:
    Date();  // Конструктор по умолчанию
    Date(int day, int month, int year);

    int GetDay() const;
    int GetMonth() const;
    int GetYear() const;

    bool IsLeap() const;
    Date NextDay() const;
    Date PreviousDay() const;
    int WeekNumber() const;
    int Duration(const Date& date) const;
    std::string ToString() const;

private:
    int day;
    int month;
    int year;

    bool IsValidDate(int d, int m, int y) const;
    int DaysInMonth(int m, int y) const;
    int ToDays() const;
};

#endif
