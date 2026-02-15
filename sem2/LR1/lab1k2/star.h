#pragma once
#include <QVector>
#include <QPointF>
#include "shape.h"
#include <QPainter>

class Star:public Shape
{
    double innerRad;
    double outterRad;
    QVector<QPointF> vertices;

public:
    Star(QPointF c, double a);
    void draw(QPainter &p) override;
    bool contains(QPointF p) override;
    bool isRotateZone(QPointF p);

    QVector<QPointF> getVertices() const;
    QVector<QPointF> getHandles() const override;

    HitType hitTest(QPointF p) override;
    void resizeBy(QPointF delta, int handle) override;
};
