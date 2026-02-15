#include "star.h"
#include <QVector>
#include <QPointF>
#include "shape.h"
#include <QPainter>
#include "cmath"
Star::Star(QPointF c, double a): Shape(c) {
    double deg=M_PI/180.0;
    outterRad = a / (2 * sin(36 * deg));
    innerRad  = outterRad * sin(18 * deg) / sin(54 * deg);

    double angle = -90*deg;
    double step=36*deg;
    for(int i=0;i<10; i++){
        double r=(i%2==0)? outterRad:innerRad;
        vertices.append(QPointF(r*cos(angle), r*sin(angle)));
        angle+=step;
    }
}

QVector<QPointF> Star::getVertices() const {
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

void Star::draw(QPainter &p) {
    p.save();
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(color);
    p.drawPolygon(getVertices());
    p.restore();
}



bool Star::isRotateZone(QPointF p)
{
    double d = QLineF(p, center).length();

    double R = QLineF(getVertices()[0], center).length();
    double inner = R * 1.05;
    double outer = R * 1.25;

    return d > inner && d < outer;
}



QVector<QPointF> Star::getHandles() const {
    QVector<QPointF> h;
    auto v = getVertices();
    for (int i = 0; i < v.size(); i += 2)
        h.append(v[i]);
    return h;
}

//возвращение во что попали и что с ней сделать
HitType Star::hitTest(QPointF p)
{
    auto handles = getHandles();
    double r = 8;

    for (int i = 0; i < handles.size(); ++i) {
        if (QLineF(p, handles[i]).length() <= r) {
            activeHandle = i;
            return HitType::Handle;
        }
    }

    if (isRotateZone(p))
        return HitType::Rotate;

    if (contains(p))
        return HitType::Body;

    return HitType::None;
}




void Star::resizeBy(QPointF delta, int handle) {
    double d0 = QLineF(center, getVertices()[0]).length(); //R
    double d1 = QLineF(center, getVertices()[0] + delta).length();

    if (d0 > 1e-3) {
        scale *= d1 / d0;
    }
}
bool Star::contains(QPointF p)
{
    double d = QLineF(center, p).length();
    double R = QLineF(center, getVertices()[0]).length();

    return d <= R;
}

