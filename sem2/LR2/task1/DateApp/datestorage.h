#ifndef DATESTORAGE_H
#define DATESTORAGE_H

#include <vector>
#include <QString>
#include "date.h"

class DateStorage
{
public:
    DateStorage();

    void LoadFromFile(const QString& filename);
    void SaveToFile(const QString& filename) const;
    void AppendToFile(const QString& filename, const Date& date);
    void CreateDefaultFile(const QString& filename);
    void SetDates(const std::vector<Date>& newDates);

    const std::vector<Date>& GetDates() const;

private:
    std::vector<Date> dates;
};

#endif
