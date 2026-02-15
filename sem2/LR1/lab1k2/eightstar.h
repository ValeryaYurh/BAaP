#pragma once
#include <QVector>
#include <QPointF>
#include "shape.h"
#include <QPainter>

class EightStar:public Shape
{
    double outerR;
    double innerR;
    QVector<QPointF> vertices;

public:
    EightStar(QPointF c, double a);
    void draw(QPainter &p) override;
    bool contains(QPointF p) override;
    bool isRotateZone(QPointF p);

    QVector<QPointF> getVertices() const;
    QVector<QPointF> getHandles() const override;

    HitType hitTest(QPointF p) override;
    void resizeBy(QPointF delta, int handle) override;
};

