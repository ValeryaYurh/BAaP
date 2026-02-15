#pragma once
#include <QPainter>
#include "shape.h"
#include <QPointF>
#include <QVector>

class Sixcorner:public Shape
{
    QVector<QPointF> vertices;

public:
    Sixcorner(QPointF c, double R);

    void draw(QPainter &p) override;
    QVector<QPointF> getVertices() const;
    bool contains(QPointF p) override;
    bool isRotateZone(QPointF p);

    HitType hitTest(QPointF p) override;
    void resizeBy(QPointF delta, int handleIndex) override;
    QVector<QPointF> getHandles() const override;
};
