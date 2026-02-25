#include "date.h"
#include <stdexcept>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

Date::Date() : day(1), month(1), year(2000)
{
    // Конструктор по умолчанию - 1 января 2000 года
}

Date::Date(int day, int month, int year)
    : day(day), month(month), year(year)
{
    if (!IsValidDate(day, month, year)) {
        throw std::invalid_argument("Некорректная дата");
    }
}

int Date::GetDay() const { return day; }
int Date::GetMonth() const { return month; }
int Date::GetYear() const { return year; }

bool Date::IsValidDate(int d, int m, int y) const
{
    if (y < 1 || m < 1 || m > 12 || d < 1) return false;
    return d <= DaysInMonth(m, y);
}

int Date::DaysInMonth(int m, int y) const
{
    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && IsLeap()) return 29;
    return daysInMonth[m - 1];
}

bool Date::IsLeap() const
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

Date Date::NextDay() const
{
    int d = day + 1;
    int m = month;
    int y = year;

    if (d > DaysInMonth(m, y)) {
        d = 1;
        m++;
        if (m > 12) {
            m = 1;
            y++;
        }
    }

    return Date(d, m, y);
}

Date Date::PreviousDay() const
{
    int d = day - 1;
    int m = month;
    int y = year;

    if (d < 1) {
        m--;
        if (m < 1) {
            m = 12;
            y--;
        }
        d = DaysInMonth(m, y);
    }

    return Date(d, m, y);
}

int Date::WeekNumber() const
{
    // 1 января того же года
    Date firstJan(1, 1, year);

    // Разница в днях от 1 января
    int daysDiff = firstJan.Duration(*this);

    // Номер недели = дни от начала года / 7 + 1
    if (daysDiff < 0) return 0;

    return (daysDiff / 7) + 1;
}

int Date::ToDays() const
{
    int totalDays = 0;

    // Добавляем дни за предыдущие годы
    for (int y = 1; y < year; y++) {
        Date temp(1, 1, y);
        totalDays += temp.IsLeap() ? 366 : 365;
    }

    // Добавляем дни за предыдущие месяцы текущего года
    for (int m = 1; m < month; m++) {
        totalDays += DaysInMonth(m, year);
    }

    // Добавляем дни текущего месяца
    totalDays += day - 1;

    return totalDays;
}

int Date::Duration(const Date& date) const
{
    return date.ToDays() - ToDays();
}

std::string Date::ToString() const
{
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << day << "."
        << std::setw(2) << std::setfill('0') << month << "."
        << std::setw(4) << std::setfill('0') << year;
    return oss.str();
}
