#include "datestorage.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <stdexcept>

DateStorage::DateStorage()
{
}

void DateStorage::LoadFromFile(const QString& filename)
{
    dates.clear();
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("Не удалось открыть файл");
    }

    QTextStream in(&file);
    int lineNumber = 0;
    int skippedLines = 0;

    while (!in.atEnd()) {
        lineNumber++;
        QString line = in.readLine().trimmed();

        if (line.isEmpty()) continue;

        line = line.simplified();
        QStringList parts = line.split(".");

        if (parts.size() != 3) {
            qDebug() << "Строка" << lineNumber << "пропущена (неверный формат):" << line;
            skippedLines++;
            continue;
        }

        bool ok1, ok2, ok3;
        int day = parts[0].toInt(&ok1);
        int month = parts[1].toInt(&ok2);
        int year = parts[2].toInt(&ok3);

        if (!ok1 || !ok2 || !ok3) {
            qDebug() << "Строка" << lineNumber << "пропущена (не числа):" << line;
            skippedLines++;
            continue;
        }

        try {
            Date date(day, month, year);
            dates.push_back(date);
        } catch (const std::exception& e) {
            qDebug() << "Строка" << lineNumber << "пропущена (некорректная дата):" << line;
            skippedLines++;
        }
    }

    file.close();

    qDebug() << "Загружено дат:" << dates.size() << ", пропущено строк:" << skippedLines;

    if (skippedLines > 0) {
        qDebug() << "Внимание: некоторые строки были пропущены";
    }
}

void DateStorage::SaveToFile(const QString& filename) const
{
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error("Не удалось сохранить файл");
    }

    QTextStream out(&file);

    for (const auto& date : dates) {
        out << date.GetDay() << "." << date.GetMonth() << "." << date.GetYear() << "\n";
    }

    file.close();
}

void DateStorage::AppendToFile(const QString& filename, const Date& date)
{
    QFile file(filename);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        throw std::runtime_error("Не удалось открыть файл для добавления");
    }

    QTextStream out(&file);
    out << date.GetDay() << "." << date.GetMonth() << "." << date.GetYear() << "\n";

    file.close();
}

void DateStorage::CreateDefaultFile(const QString& filename)
{
    QFile file(filename);

    if (file.exists()) {
        qDebug() << "Файл уже существует:" << filename;
        return;
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error("Не удалось создать файл по умолчанию");
    }

    QTextStream out(&file);
    out << "01.01.2000\n";
    out << "24.04.2000\n";
    out << "29.02.2000\n";
    out << "31.12.2021\n";
    out << "09.02.2026\n";
    out << "19.02.2026\n";

    file.close();

    qDebug() << "Создан файл по умолчанию:" << filename;
}

void DateStorage::SetDates(const std::vector<Date>& newDates)
{
    dates = newDates;
}

const std::vector<Date>& DateStorage::GetDates() const
{
    return dates;
}
