#include "productfile.h"
#include <QFile>
#include <QDataStream>

bool ProductFile::saveToFile(const QString& fileName, const QVector<Product>& products)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
        return false;

    QDataStream out(&file);
    out << products.size();
    for(const Product &p: products)
        out << p.group << p.code << p.name << p.model << p.price << p.quantity;

    return true;
}

bool ProductFile::loadFromFile(const QString& fileName, QVector<Product>& products)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        return false;

    QDataStream in(&file);
    int size;
    in >> size;
    products.clear();
    for(int i=0;i<size;i++)
    {
        Product p;
        in >> p.group >> p.code >> p.name >> p.model >> p.price >> p.quantity;
        products.push_back(p);
    }
    return true;
}
