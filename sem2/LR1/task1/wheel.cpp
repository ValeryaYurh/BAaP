#include "wheel.h"
#include <QtMath>

Wheel::Wheel(double x, double y, double r, int spokesCount)
    : MovingCircle(x, y, r), angle(0), spokes(spokesCount)
{
}

void Wheel::rotate(double da)
{
    angle += da;
}

void Wheel::draw(QPainter &painter)
{
    // Рисуем круг
    MovingCircle::draw(painter);

    painter.save();
    painter.translate(center);
    painter.rotate(angle);

    for (int i = 0; i < spokes; ++i)
    {
        double a = i * (360.0 / spokes);
        double rad = qDegreesToRadians(a);
        QPointF p1(radius * qCos(rad), radius * qSin(rad));
        QPointF p2(-radius * qCos(rad), -radius * qSin(rad));
        painter.drawLine(p1, p2);
    }

    painter.restore();
}
