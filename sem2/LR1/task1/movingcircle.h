#ifndef MOVINGCIRCLE_H
#define MOVINGCIRCLE_H

#include <QPointF>
#include <QPainter>

class MovingCircle
{
protected:
    QPointF center;
    double radius;

public:

    MovingCircle(double x, double y, double r);

    virtual ~MovingCircle() {}

    virtual void draw(QPainter &painter);
    void move(double dx, double dy);
};

#endif
