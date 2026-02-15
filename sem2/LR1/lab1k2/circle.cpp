#include "circle.h"
#include <QLineF>
#include <cmath>

Circle::Circle(QPointF c, double r)
    : Shape(c), radius(r) {}

void Circle::draw(QPainter &p)
{
    p.save();
    p.translate(center);
    p.rotate(rotation);
    p.scale(scale, scale);
    p.setPen(Qt::NoPen);
    p.setBrush(color);
    p.drawEllipse(QPointF(0,0), radius, radius);
    p.restore();
}

QVector<QPointF> Circle::getHandles() const
{
    return { center + QPointF(radius*scale, 0) };
}

HitType Circle::hitTest(QPointF p)
{
    double dist = QLineF(p, center).length();

    for (int i=0;i<getHandles().size();++i)
        if (QLineF(p,getHandles()[i]).length() <= 8.0) {
            activeHandle = i;
            return HitType::Handle;
        }

    if (dist <= radius*scale) return HitType::Body;
    if (dist <= radius*scale + 10) return HitType::Rotate;
    return HitType::None;
}

//меняем радиус
void Circle::resizeBy(QPointF delta, int handleIndex)
{
    Q_UNUSED(handleIndex);
    double dr = delta.x(); // тянем по X
    radius += dr / scale;
    if (radius < 5) radius = 5;
}
bool Circle::contains(QPointF p) {
    double dist = QLineF(p, center).length();
    return dist <= radius * scale;
}

