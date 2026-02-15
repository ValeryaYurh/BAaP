#include "rectangle.h"
#include <QVector>
#include <QPointF>
#include "shape.h"
#include <QPainter>

Rectangle::Rectangle(QPointF c, double height, double width): Shape(c) {
    double hw=width/2;
    double hh=height/2;
    vertices={{-hw, -hh},
                { hw, -hh},
                { hw,  hh},
                {-hw,  hh} //vertices from (0,0)
    };
}

QVector<QPointF> Rectangle::getVertices() const {
    QVector<QPointF> absVertices;
    double rad = rotation * M_PI / 180.0;

    for (auto &v : vertices) {
        double x = v.x() * scale;
        double y = v.y() * scale;

        double xr = x * cos(rad) - y * sin(rad);
        double yr = x * sin(rad) + y * cos(rad);

        absVertices.append(center+QPointF(xr,yr));
    }

    return absVertices;
}

void Rectangle::draw(QPainter &p) {
    p.save();
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(color);
    p.drawPolygon(getVertices());
    p.restore();
}



bool Rectangle::isRotateZone(QPointF p) {
    double d=QLineF(p,center).length();
    return d>1.1*QLineF(getVertices()[0], center).length();
}

// void Rectangle::setVertices(QPointF v1, QPointF v2, QPointF v3, QPointF v4) {
//     vertices = {v1 - center, v2 - center, v3 - center, v4 - center};
// }

QVector<QPointF> Rectangle::getHandles() const {
    return getVertices();
}

HitType Rectangle::hitTest(QPointF p) {
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

void Rectangle::resizeBy(QPointF delta, int handle) {
    vertices[handle]+=delta/scale;
}
bool Rectangle::contains(QPointF p) {
    // Проверяем попадание внутрь
    QPolygonF poly(getVertices());
    return poly.containsPoint(p, Qt::OddEvenFill);
}

