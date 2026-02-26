#ifndef PRODUCTFILE_H
#define PRODUCTFILE_H

#include <QVector>
#include <QString>
#include "product.h"

class ProductFile
{
public:
    static bool saveToFile(const QString& fileName, const QVector<Product>& products);
    static bool loadFromFile(const QString& fileName, QVector<Product>& products);
};

#endif
