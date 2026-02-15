#pragma once
#include "shape.h"
#include <QPainter>
#include <QPointF>

class Circle : public Shape
{
    double radius;

public:
    Circle(QPointF c, double r);

    void draw(QPainter &p) override;
    bool contains(QPointF p) override;

    QVector<QPointF> getHandles() const override;
    HitType hitTest(QPointF p) override;
    void resizeBy(QPointF delta, int handleIndex) override;

    void setColor(const QColor &c) override {color=c;}
    QColor selectColor()const override {return color;}
};
