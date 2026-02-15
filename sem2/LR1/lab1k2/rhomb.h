#pragma once
#include <QVector>
#include <QPointF>
#include <QPainter>
#include "shape.h"
#include <QPolygonF>
#include <cmath>

class Rhomb : public Shape
{
    QVector<QPointF> vertices;

public:
    Rhomb(QPointF c, QPointF v1, QPointF v2, QPointF v3, QPointF v4);

    void draw(QPainter &p) override;
    bool contains(QPointF p) override;
    bool isRotateZone(QPointF p);

    QVector<QPointF> getVertices() const;
    QVector<QPointF> getHandles() const override;

    HitType hitTest(QPointF p) override;
    void resizeBy(QPointF delta, int handle) override;
};
