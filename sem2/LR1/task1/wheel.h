#ifndef WHEEL_H
#define WHEEL_H

#include "movingcircle.h"

class Wheel : public MovingCircle
{
private:
    double angle;
    int spokes;

public:

    Wheel(double x, double y, double r, int spokesCount = 4);

    void rotate(double da);
    void draw(QPainter &painter) override;
};

#endif // WHEEL_H
