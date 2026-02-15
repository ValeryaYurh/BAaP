#pragma once
#include <QVector>
#include <QPointF>
#include "shape.h"
#include <QPainter>

class Square: public Shape
{
    QVector<QPointF> vertices;
public:
    Square(QPointF c, double height, double width);
    void draw(QPainter &p) override;
    bool contains(QPointF p) override;
    bool isRotateZone(QPointF p);

    QVector<QPointF> getVertices() const;
    QVector<QPointF> getHandles() const override;

    HitType hitTest(QPointF p) override;
    void resizeBy(QPointF delta, int handle) override;
};


