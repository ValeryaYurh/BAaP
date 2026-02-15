#include "sixstar.h"
#include "shape.h"
#include <cmath>
#include <QPolygonF>

SixStar::SixStar(QPointF c, double a): Shape(c) {
    double deg=M_PI/180.0;
    double R=a;

    for(int i=0;i<3; i++){//up triangle
        double angle=-90*deg+i*120*deg;
        vertices.append(QPointF(R*cos(angle), R*sin(angle)));
    }
    for(int i=0;i<3;++i){//down triangle
        double angle=90*deg+i*120*deg;
        vertices.append(QPointF(R*cos(angle), R*sin(angle)));
    }
}

QVector<QPointF> SixStar::getVertices() const {
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

void SixStar::draw(QPainter &p) {
    p.save();
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(color);
    auto v=getVertices();
    p.drawPolygon(QPolygonF({v[0], v[1],v[2]}));
    p.drawPolygon(QPolygonF({v[3], v[4],v[5]}));
    p.restore();
}



bool SixStar::isRotateZone(QPointF p)
{
    double d = QLineF(p, center).length();

    double R = QLineF(getVertices()[0], center).length();
    double inner = R * 1.05;
    double outer = R * 1.25;

    return d > inner && d < outer;
}



QVector<QPointF> SixStar::getHandles() const {
    QVector<QPointF> h;
    auto v = getVertices();
    for (int i = 0; i < v.size(); i += 2)
        h.append(v[i]);
    return h;
}

//возвращение во что попали и что с ней сделать
HitType SixStar::hitTest(QPointF p)
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




void SixStar::resizeBy(QPointF delta, int handle) {
    double d0 = QLineF(center, getVertices()[0]).length(); //R
    double d1 = QLineF(center, getVertices()[0] + delta).length();

    if (d0 > 1e-3) {
        scale *= d1 / d0;
    }
}
bool SixStar::contains(QPointF p)
{
    double d = QLineF(center, p).length();
    double R = QLineF(center, getVertices()[0]).length();

    return d <= R;
}

