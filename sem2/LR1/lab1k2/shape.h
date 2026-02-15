#pragma once
#include <QPointF>
#include <QVector>
#include <QPainter>
#include <QColor>
enum class HitType {
    None,
    Body,
    Rotate,
    Handle
};

class Shape
{
protected:
    QPointF center;
    double rotation = 0;
    double scale = 1.0;
    QColor color=Qt::yellow;


public:
    int activeHandle = -1;

    Shape(QPointF c) : center(c) {}
    virtual ~Shape() = default;
    virtual bool contains(QPointF p)=0;
    virtual void draw(QPainter &p) = 0;

    void moveBy(QPointF delta) { center += delta; }
    void rotateBy(double angle) { rotation += angle; }
    void scaleBy(double factor) { scale *= factor; }

    QPointF getCenter() const { return center; }
    //возвращение во что попали и что с ней сделать
    virtual HitType hitTest(QPointF p) = 0;
    virtual void resizeBy(QPointF delta, int handleIndex) = 0;
    virtual QVector<QPointF> getHandles() const = 0;

    virtual void setColor(const QColor &c){color=c;}
    virtual QColor selectColor()const{return color;}
};
