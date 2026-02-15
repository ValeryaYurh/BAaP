#pragma once
#include "shape.h"
#include <QPointF>
#include <QVector>
#include <QPainter>

class Triangle : public Shape
{
    QVector<QPointF> vertices;

public:
    Triangle(QPointF c, QPointF v1, QPointF v2, QPointF v3);

    void draw(QPainter &p) override;
    QVector<QPointF> getVertices() const;
    bool contains(QPointF p) override;
    bool isRotateZone(QPointF p);

    HitType hitTest(QPointF p) override;
    void resizeBy(QPointF delta, int handleIndex) override;
    QVector<QPointF> getHandles() const override;
};
