#include "movingcircle.h"

MovingCircle::MovingCircle(double x, double y, double r)
    : center(x, y), radius(r)
{

}

void MovingCircle::draw(QPainter &painter)
{
    painter.drawEllipse(center, radius, radius);
}

void MovingCircle::move(double dx, double dy)
{
    center.rx() += dx;
    center.ry() += dy;
}
