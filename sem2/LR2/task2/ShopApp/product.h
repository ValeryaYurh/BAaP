#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QDebug>

class Product
{
public:
    Product() : price(0.0), quantity(0) {}  // Конструктор по умолчанию с инициализацией

    Product(QString group, QString code, QString name,
            QString model, double price, int quantity)
        : group(group), code(code), name(name),
        model(model), price(price), quantity(quantity)
    {
        // Для отладки
        qDebug() << "Product created with price:" << price;
    }

    QString group;
    QString code;
    QString name;
    QString model;
    double price;
    int quantity;
};

#endif
