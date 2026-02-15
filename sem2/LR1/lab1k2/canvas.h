#ifndef CANVAS_H
#define CANVAS_H
#include <QColor>
#include <QWidget>
#include "shape.h"
enum InteractionMode {
    None,
    Drag,
    Rotate,
    DrawCircle,
    DrawTriangle,
    DrawRhomb,
    DrawRectangle,
    DrawSquare,
    DrawStar,
    DrawSixStar,
    DrawEightStar,
    DrawTrapez,
    DrawSixcorner,
    Resize
};


class Canvas : public QWidget {
    Q_OBJECT

    Shape *activeShape = nullptr;
    InteractionMode mode = None;


    QPointF lastMousePos;
    double startAngle = 0;
    int activeHandle=-1;

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void wheelEvent(QWheelEvent *event) override;

public:
    void setMode(InteractionMode m) { mode = m; }
    explicit Canvas(QWidget *parent = nullptr);
    QVector<Shape*> shapes;
    Shape* getActiveShape() const {return activeShape;}
    void setActiveShapeColor(const QColor &c){
        if(activeShape) activeShape->setColor(c);
    }
    bool colorMode=false;
    QColor selectedColor;

};

#endif
