#include "sixcorner.h"
#include <QLineF>
#include <QPointF>
#include <QPainter>
#include <QPolygonF>
#include <cmath>
#include "shape.h"

Sixcorner::Sixcorner(QPointF c, double R):Shape(c){
    double step = 2 * M_PI / 6;
    double angle = -M_PI / 2;

    for (int i = 0; i < 6; ++i) {
        vertices.append(QPointF(
            R * cos(angle),
            R * sin(angle)
            ));
        angle += step;
    }
}


void Sixcorner::draw(QPainter &p){
    p.save();
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(color);
    p.drawPolygon(getVertices());
    p.restore();
}
QVector<QPointF> Sixcorner::getVertices() const{
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
bool Sixcorner::contains(QPointF p){
    QPolygonF poly(getVertices());
    return poly.containsPoint(p, Qt::OddEvenFill);

}
bool Sixcorner::isRotateZone(QPointF p){
    double d = QLineF(p, center).length();

    double R = 0;
    for (auto &v : getVertices())
        R = std::max(R, QLineF(center, v).length());

    return d > R * 1.05 && d < R * 1.25;

}

HitType Sixcorner::hitTest(QPointF p){
    auto handles = getHandles();
    double r = 8;

    for (int i = 0; i < handles.size(); ++i) {
        if (QLineF(p, handles[i]).length() <= r) {
            activeHandle = i;
            return HitType::Handle;
        }
    }

    if (isRotateZone(p)) return HitType::Rotate;
    if (contains(p)) return HitType::Body;

    return HitType::None;

}
void Sixcorner::resizeBy(QPointF delta, int handleIndex){
    if (handleIndex < 0 || handleIndex >= vertices.size()) return;
    vertices[handleIndex] += delta / scale;

}
QVector<QPointF> Sixcorner::getHandles() const {
    return getVertices();

}
