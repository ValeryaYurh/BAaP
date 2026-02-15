#include <QPointF>
#include <QVector>
#include "shape.h"
#include <QPolygonF>

#include "rhomb.h"

Rhomb::Rhomb(QPointF c, QPointF v1, QPointF v2, QPointF v3, QPointF v4)
    : Shape(c)
{
    vertices = {v1 , v2 , v3, v4}; // сохраняем локально относительно центра
}

QVector<QPointF> Rhomb::getVertices() const {
    QVector<QPointF> absVertices;
    double rad = rotation * M_PI / 180.0;

    for (const auto &v : vertices) {
        double x = v.x() * scale;
        double y = v.y() * scale;

        double xr = x * cos(rad) - y * sin(rad);
        double yr = x * sin(rad) + y * cos(rad);

        absVertices.append(QPointF(center.x() + xr, center.y() + yr));
    }

    return absVertices;
}

void Rhomb::draw(QPainter &p) {
    p.save();
    p.setRenderHint(QPainter::Antialiasing);

    QVector<QPointF> absVertices = getVertices();

    p.setPen(Qt::NoPen);
    p.setBrush(color);
    p.drawPolygon(absVertices);

    p.restore();
}



bool Rhomb::isRotateZone(QPointF p) {
    double threshold = 10.0;
    auto absVertices = getVertices();

    for (int i = 0; i < 4; ++i) {
        QPointF a = absVertices[i];
        QPointF b = absVertices[(i + 1) % 4];
        double num = std::abs((b.y() - a.y()) * p.x() - (b.x() - a.x()) * p.y() + b.x() * a.y() - b.y() * a.x());
        double den = std::hypot(b.y() - a.y(), b.x() - a.x());
        double distance = num / den;
        if (distance <= threshold) return true;
    }

    return false;
}

// void Rhomb::setVertices(QPointF v1, QPointF v2, QPointF v3, QPointF v4) {
//     vertices = {v1 - center, v2 - center, v3 - center, v4 - center};
// }

QVector<QPointF> Rhomb::getHandles() const {
    return getVertices();
}

HitType Rhomb::hitTest(QPointF p) {
    auto handles = getHandles();
    double r = 8; // радиус ручки

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

void Rhomb::resizeBy(QPointF delta, int handle) {
    vertices[handle] += delta;

    // Пересчёт центра как среднего всех вершин
    QPointF newCenter;
    for (auto &v : vertices) newCenter += v;
    newCenter /= vertices.size();

    // Переводим вершины в локальные координаты относительно нового центра
    for (auto &v : vertices) v -= newCenter;

    // Смещаем глобальный центр
    center += newCenter;
}
bool Rhomb::contains(QPointF p) {
    // Проверяем попадание внутрь
    QPolygonF poly(getVertices());
    return poly.containsPoint(p, Qt::OddEvenFill);
}

