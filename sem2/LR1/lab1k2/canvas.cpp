#include "canvas.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <cmath>
#include "circle.h"
#include "triangle.h"
#include "rhomb.h"
#include "rectangle.h"
#include "square.h"
#include "star.h"
#include "sixstar.h"
#include "eightstar.h"
#include "trapez.h"
#include "sixcorner.h"
Canvas::Canvas(QWidget *parent) : QWidget(parent) {
    setMouseTracking(true);
}

void Canvas::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    for (auto s : shapes)
        s->draw(p);
}

void Canvas::mousePressEvent(QMouseEvent *e) {
    if (mode == DrawCircle) {
        Circle* c = new Circle(e->pos(), 50);
        shapes.append(c);
        mode = None;
        update();
        return;
    }
    if (mode == DrawTriangle) {
        QPointF c = e->pos();
        double r = 50;
        QPointF v1(c.x(), c.y() - r);
        QPointF v2(c.x() - r * sin(M_PI / 3), c.y() + r/2);
        QPointF v3(c.x() + r * sin(M_PI / 3), c.y() + r/2);

        Triangle* t = new Triangle(c, v1, v2, v3);
        shapes.append(t);

        mode = None;
        update();
        return;
    }
    if(mode==DrawRhomb){
        QPointF c=e->pos();
        double r=50;
        Rhomb* rmb = new Rhomb(
            c,
            QPointF(0, -r),
            QPointF(r, 0),
            QPointF(0, r),
            QPointF(-r, 0)
            );
        shapes.append(rmb);
        mode=None;
        update();
        return;
    }
    if(mode==DrawRectangle){
        QPointF c=e->pos();
        Rectangle* rect=new Rectangle(c, 100,60);
        shapes.append(rect);
        mode=None;
        update();
        return;
    }
    if(mode==DrawSquare){
        QPointF c=e->pos();
        Square* square=new Square(c, 80,80);
        shapes.append(square);
        mode=None;
        update();
        return;
    }
    if(mode==DrawStar){
        QPointF c=e->pos();
        Star* star=new Star(c, 80);
        shapes.append(star);

        mode=None;
        update();
        return;
    }

    if(mode==DrawSixStar){
        QPointF c=e->pos();
        SixStar* sixStar=new SixStar(c, 80);
        shapes.append(sixStar);

        mode=None;
        update();
        return;
    }
    if(mode==DrawEightStar){
        QPointF c=e->pos();
        EightStar* eightStar=new EightStar(c, 80);
        shapes.append(eightStar);

        mode=None;
        update();
        return;
    }
    if(mode==DrawTrapez){
        QPointF c=e->pos();
        double topWidth = 60;
        double bottomWidth = 120;
        double height = 80;

        QPointF v1(c.x() - topWidth / 2, c.y() - height / 2);
        QPointF v2(c.x() + topWidth / 2, c.y() - height / 2);
        QPointF v3(c.x() + bottomWidth / 2, c.y() + height / 2);
        QPointF v4(c.x() - bottomWidth / 2, c.y() + height / 2);

        Trapez* trapez = new Trapez(c, v1, v2, v3, v4);
        shapes.append(trapez);
        mode=None;
        update();
        return;
    }
    if(mode==DrawSixcorner){
        QPointF c=e->pos();
        Sixcorner* sixCorner = new Sixcorner(c,80);
        shapes.append(sixCorner);
        mode=None;
        update();
        return;
    }
    if(colorMode){
        for (auto it = shapes.rbegin(); it!=shapes.rend(); ++it) {
            if((*it)->contains(e->pos())){
                (*it)->setColor(selectedColor);
                setCursor(Qt::ArrowCursor);
                colorMode=false;
                update();
                return;
            }

        }
        return;
    }
    if (mode == None) {
        for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
            HitType hit = (*it)->hitTest(e->pos());
            if (hit != HitType::None) {
                activeShape = *it;
                lastMousePos = e->pos();

                if (hit == HitType::Rotate)
                    mode = Rotate;
                else if (hit == HitType::Handle) {
                    mode = Resize;
                    activeHandle = activeShape->activeHandle;
                } else
                    mode = Drag;

                return;
            }
        }
    }
    for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
        HitType hit = (*it)->hitTest(e->pos());

        if (hit != HitType::None) {
            activeShape = *it;
            lastMousePos = e->pos();

            if (hit == HitType::Rotate) {
                mode = Rotate;

                QPointF c = activeShape->getCenter();
                startAngle = std::atan2(
                    e->pos().y() - c.y(),
                    e->pos().x() - c.x()
                    );
            }
            else if (hit == HitType::Handle) {
                mode = Resize;
                activeHandle = activeShape->activeHandle;
            }
            else {
                mode = Drag;
            }

            return;
        }
    }

}

void Canvas::mouseMoveEvent(QMouseEvent *e) {
    if (!activeShape) return;

    if (mode == Drag) {
        QPointF delta = e->pos() - lastMousePos;
        activeShape->moveBy(delta);
        lastMousePos = e->pos();
    }

    if (mode == Rotate) {
        QPointF c = activeShape->getCenter();

        double currentAngle = std::atan2(
            e->pos().y() - c.y(),
            e->pos().x() - c.x()
            );

        double deltaAngle = (currentAngle - startAngle) * 180.0 / M_PI;
        activeShape->rotateBy(deltaAngle);

        startAngle = currentAngle;
    }
    if(mode==Resize){
        QPointF delta=e->pos()-lastMousePos;
        activeShape->resizeBy(delta, activeHandle);
        lastMousePos=e->pos();
    }

    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *) {
    activeShape = nullptr;
    activeHandle=-1;
    mode = None;
}

void Canvas::wheelEvent(QWheelEvent *event) {
    if (activeShape) {
        double factor = 1.0 + event->angleDelta().y() / 1200.0;
        activeShape->scaleBy(factor);
        update();
    }
}
