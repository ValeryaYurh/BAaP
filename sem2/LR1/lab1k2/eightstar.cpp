#include "eightstar.h"
#include <QVector>
#include <QPointF>
#include "shape.h"
#include <QPainter>

EightStar::EightStar(QPointF c, double a):Shape(c) {
    double deg=M_PI/180.0;
    outerR = a / (2 * sin(M_PI / 8));
    innerR = outerR * sin(M_PI / 8) / sin(3 * M_PI / 8);
    double angle = -90*deg;
    double step=360.0/16.0*deg;
    for(int i=0;i<16; i++){
        double r=(i%2==0) ? outerR : innerR;
        vertices.append(QPointF(r*cos(angle), r*sin(angle)));
        angle+=step;
    }
}
QVector<QPointF> EightStar::getVertices() const
{
    QVector<QPointF> abs;
    double rad = rotation * M_PI / 180.0;

    for (auto &v : vertices) {
        double x = v.x() * scale;
        double y = v.y() * scale;

        double xr = x * cos(rad) - y * sin(rad);
        double yr = x * sin(rad) + y * cos(rad);

        abs.append(center + QPointF(xr, yr));
    }
    return abs;
}

void EightStar::draw(QPainter &p)
{
    p.save();
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(color);
    p.drawPolygon(getVertices());
    p.restore();
}

bool EightStar::isRotateZone(QPointF p)
{
    double d = QLineF(p, center).length();
    double R = QLineF(center, getVertices()[0]).length();

    return d > R * 1.05 && d < R * 1.25;
}

QVector<QPointF> EightStar::getHandles() const
{
    QVector<QPointF> h;
    auto v = getVertices();
    for (int i = 0; i < v.size(); i += 2)
        h.append(v[i]);
    return h;
}


HitType EightStar::hitTest(QPointF p)
{
    if (contains(p))
        return HitType::Body;

    auto handles = getHandles();
    for (int i = 0; i < handles.size(); ++i) {
        if (QLineF(p, handles[i]).length() <= 8) {
            activeHandle = i;
            return HitType::Handle;
        }
    }

    if (isRotateZone(p))
        return HitType::Rotate;

    return HitType::None;
}

bool EightStar::contains(QPointF p)
{
    return QPolygonF(getVertices()).containsPoint(p, Qt::OddEvenFill);
}

void EightStar::resizeBy(QPointF delta, int)
{
    double d0 = QLineF(center, getVertices()[0]).length();
    double d1 = QLineF(center, getVertices()[0] + delta).length();

    if (d0 > 1e-3)
        scale *= d1 / d0;
}
