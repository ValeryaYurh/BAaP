#include "triangle.h"
#include <QLineF>
#include <QPointF>
#include <QPainter>
#include <cmath>

Triangle::Triangle(QPointF c, QPointF v1, QPointF v2, QPointF v3)
    : Shape(c)
{
    vertices = { v1 - c, v2 - c, v3 - c };
}

QVector<QPointF> Triangle::getVertices() const
{
    QVector<QPointF> absVertices;
    double rad = rotation * M_PI / 180.0;

    for (const auto &v : vertices) {
        double x = v.x() * scale;
        double y = v.y() * scale;
        double xr = x * cos(rad) - y * sin(rad);
        double yr = x * sin(rad) + y * cos(rad);
        absVertices.append(center + QPointF(xr, yr));
    }
    return absVertices;
}

void Triangle::draw(QPainter &p)
{
    p.save();
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(color);
    p.drawPolygon(getVertices());
    p.restore();
}

QVector<QPointF> Triangle::getHandles() const
{
    return getVertices();
}

HitType Triangle::hitTest(QPointF p)
{
    if (contains(p))
        return HitType::Body;

    auto handles = getHandles();
    double handleRadius = 8.0;

    for (int i = 0; i < handles.size(); ++i) {
        if (QLineF(p, handles[i]).length() <= handleRadius) {
            activeHandle = i;
            return HitType::Handle;
        }
    }

    if (isRotateZone(p))
        return HitType::Rotate;

    return HitType::None;
}


void Triangle::resizeBy(QPointF delta, int handleIndex)
{
    if (handleIndex < 0 || handleIndex >= vertices.size()) return;

    //лок вершина + масштабируем на delta
    QPointF local = vertices[handleIndex];
    QPointF newPos = local + delta / scale;
    vertices[handleIndex] = newPos;
}
bool Triangle::contains(QPointF p) {
    // попадание в треугольник через барицентрические координаты
    QVector<QPointF> verts = getVertices();
    double denominator = ((verts[1].y() - verts[2].y()) * (verts[0].x() - verts[2].x()) +
                          (verts[2].x() - verts[1].x()) * (verts[0].y() - verts[2].y()));
    double a = ((verts[1].y() - verts[2].y()) * (p.x() - verts[2].x()) +
                (verts[2].x() - verts[1].x()) * (p.y() - verts[2].y())) / denominator;
    double b = ((verts[2].y() - verts[0].y()) * (p.x() - verts[2].x()) +
                (verts[0].x() - verts[2].x()) * (p.y() - verts[2].y())) / denominator;
    double c = 1 - a - b;

    return (a >= 0) && (b >= 0) && (c >= 0);
}
bool Triangle::isRotateZone(QPointF p)
{
    double d = QLineF(p, center).length();

    // максимальный радиус вершины
    double R = 0;
    for (auto &v : getVertices())
        R = std::max(R, QLineF(center, v).length());

    double inner = R * 1.05;
    double outer = R * 1.25;

    return d > inner && d < outer;
}
