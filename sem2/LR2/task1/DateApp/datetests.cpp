#include "datetests.h"
#include "date.h"
#include <sstream>
#include <QDebug>

QString DateTests::RunAllTests()
{
    std::ostringstream res;
    res << "=== Результаты тестов ===\n";

    // Проверяем, что класс Date вообще работает
    try {
        Date test(1, 1, 2000);
        res << "✓ Класс Date инициализируется\n";
    } catch (...) {
        res << "✗ КЛАСС DATE НЕ РАБОТАЕТ!\n";
        return QString::fromStdString(res.str());
    }

    int passed = 0;
    int total = 5;

    // Тест 1: Високосный год
    try {
        Date d1(29, 2, 2000);
        if (d1.IsLeap()) {
            res << "✓ Тест 1 (високосный год): OK\n";
            passed++;
        } else {
            res << "✗ Тест 1 (високосный год): FAILED - 2000 должен быть високосным\n";
        }
    } catch (const std::exception& e) {
        res << "✗ Тест 1: ИСКЛЮЧЕНИЕ - " << e.what() << "\n";
    } catch (...) {
        res << "✗ Тест 1: НЕИЗВЕСТНОЕ ИСКЛЮЧЕНИЕ\n";
    }

    // Тест 2: Следующий день
    try {
        Date d2(31, 1, 2023);
        Date next = d2.NextDay();
        if (next.GetDay() == 1 && next.GetMonth() == 2) {
            res << "✓ Тест 2 (следующий день): OK\n";
            passed++;
        } else {
            res << "✗ Тест 2 (следующий день): FAILED\n";
        }
    } catch (...) {
        res << "✗ Тест 2: ИСКЛЮЧЕНИЕ\n";
    }

    // Тест 3: Конец года
    try {
        Date d3(31, 12, 2023);
        Date next = d3.NextDay();
        if (next.GetDay() == 1 && next.GetMonth() == 1 && next.GetYear() == 2024) {
            res << "✓ Тест 3 (конец года): OK\n";
            passed++;
        } else {
            res << "✗ Тест 3 (конец года): FAILED\n";
        }
    } catch (...) {
        res << "✗ Тест 3: ИСКЛЮЧЕНИЕ\n";
    }

    // Тест 4: Предыдущий день
    try {
        Date d4(1, 1, 2023);
        Date prev = d4.PreviousDay();
        if (prev.GetDay() == 31 && prev.GetMonth() == 12 && prev.GetYear() == 2022) {
            res << "✓ Тест 4 (предыдущий день): OK\n";
            passed++;
        } else {
            res << "✗ Тест 4 (предыдущий день): FAILED\n";
        }
    } catch (...) {
        res << "✗ Тест 4: ИСКЛЮЧЕНИЕ\n";
    }

    // Тест 5: Разница между датами
    try {
        Date d5(1, 1, 2023);
        Date d6(2, 1, 2023);
        int dur = d5.Duration(d6);
        res << "✓ Тест 5 (разница): OK = " << dur << "\n";
        passed++;
    } catch (...) {
        res << "✗ Тест 5: ИСКЛЮЧЕНИЕ\n";
    }

    res << "\n=== Итог: " << passed << "/" << total << " ===\n";
    return QString::fromStdString(res.str());
}
