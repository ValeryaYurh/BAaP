#include "trapez.h"
#include <QLineF>
#include <QPointF>
#include <QPainter>
#include <QPolygonF>
#include <cmath>
#include "shape.h"

Trapez::Trapez(QPointF c, QPointF v1, QPointF v2, QPointF v3, QPointF v4):Shape(c) {
    vertices={
        c-v1,c-v2,c-v3,c-v4
    };
}

QVector<QPointF> Trapez::getVertices() const{
    QVector<QPointF> absVertices;
    double rad = rotation * M_PI / 180.0;

    for (const auto &v : vertices) {
        double x = v.x() * scale;
        double y = v.y() * scale;
        double xr = x * cos(rad) - y * sin(rad);
        double yr = x * sin(rad) + y * cos(rad);
        absVertices.append(center + QPointF(xr, yr));
    }
    return absVertices;
}

void Trapez::draw(QPainter &p){
    p.save();
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(color);
    p.drawPolygon(getVertices());
    p.restore();
}


bool Trapez::contains(QPointF p) {
    QPolygonF poly(getVertices());
    return poly.containsPoint(p, Qt::OddEvenFill);
}
bool Trapez::isRotateZone(QPointF p){
    double d = QLineF(p, center).length();

    double R = 0;
    for (auto &v : getVertices())
        R = std::max(R, QLineF(center, v).length());

    return d > R * 1.05 && d < R * 1.25;
}

HitType Trapez::hitTest(QPointF p){
    if (contains(p))
        return HitType::Body;

    auto handles = getHandles();
    double handleRadius = 8.0;

    for (int i = 0; i < handles.size(); ++i) {
        if (QLineF(p, handles[i]).length() <= handleRadius) {
            activeHandle = i;
            return HitType::Handle;
        }
    }

    if (isRotateZone(p))
        return HitType::Rotate;

    return HitType::None;

}
void Trapez::resizeBy(QPointF delta, int handleIndex){
    if (handleIndex < 0 || handleIndex >= vertices.size())
        return;

    QPointF local = vertices[handleIndex];
    vertices[handleIndex] = local + delta / scale;

}
QVector<QPointF> Trapez::getHandles() const{
    return getVertices();
}
