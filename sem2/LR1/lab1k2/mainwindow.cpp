#include "mainwindow.h"
#include <QToolBar>
#include <QAction>
#include <QPalette>
#include <QApplication>
#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <QDebug>
#include <QPushButton>
#include <QObject>
#include <QCursor>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    canvas = new Canvas(this);
    setCentralWidget(canvas);

    QToolBar *toolBar = addToolBar("Shapes");

    QAction *circleAction = new QAction(
        QIcon(":/images/circle.png"),
        "Circle",
        this
        );
    QAction *triangleAction = new QAction(
        QIcon(":/images/triangle.png"),
        "Triangle",
        this
        );
    QAction *rhombAction = new QAction(
        QIcon(":/images/rhomb.png"),
        "Rhomb",
        this
        );
    QAction *squareAction = new QAction(
        QIcon(":/images/square.png"),
        "Square",
        this
        );
    QAction *rectangleAction = new QAction(
        QIcon(":/images/rectangle.png"),
        "Rectangle",
        this
        );
    QAction *starAction = new QAction(
        QIcon(":/images/star.png"),
        "Star",
        this
        );
    QAction *starSixAction = new QAction(
        QIcon(":/images/sixPointedStar.png"),
        "sixPointedStar",
        this
        );
    QAction *starEightAction = new QAction(
        QIcon(":/images/eightPointerStar.png"),
        "eightPointedStar",
        this
        );
    QAction *sixCornerAction = new QAction(
        QIcon(":/images/sixCornerFigure.png"),
        "sixCornerFigure",
        this
        );
    QAction *trapezAction = new QAction(QIcon(":/images/trapezoid.png"),
                                  "trapezoid",
                                  this);
    QAction *pipetteAction = new QAction(QIcon(":/images/pipette.png"),
                                        "pipette",
                                        this);


    toolBar->addAction(circleAction);
    toolBar->addAction(triangleAction);
    toolBar->addAction(rhombAction);
    toolBar->addAction(squareAction);
    toolBar->addAction(rectangleAction);
    toolBar->addAction(starAction);
    toolBar->addAction(starSixAction);
    toolBar->addAction(starEightAction);
    toolBar->addAction(sixCornerAction);
    toolBar->addAction(trapezAction);
    toolBar->addAction(pipetteAction);


    connect(circleAction, &QAction::triggered, this, [=]() {
        canvas->setMode(DrawCircle);
    });

    connect(triangleAction, &QAction::triggered, this, [=]() {
        canvas->setMode(DrawTriangle);
    });
    connect(rhombAction, &QAction::triggered, this, [=]() {
        canvas->setMode(DrawRhomb);
    });
    connect(squareAction, &QAction::triggered, this, [=]() {
        canvas->setMode(DrawSquare);
    });
    connect(rectangleAction, &QAction::triggered, this, [=]() {
        canvas->setMode(DrawRectangle);
    });
    connect(starAction, &QAction::triggered, this, [=]() {
        canvas->setMode(DrawStar);
    });
    connect(starSixAction, &QAction::triggered, this, [=]() {
        canvas->setMode(DrawSixStar);
    });
    connect(starEightAction, &QAction::triggered, this, [=]() {
        canvas->setMode(DrawEightStar);
    });
    connect(sixCornerAction, &QAction::triggered, this, [=]() {
        canvas->setMode(DrawSixcorner);
    });
    connect(trapezAction, &QAction::triggered, this, [=](){
        canvas->setMode(DrawTrapez);
    });
    connect(pipetteAction, &QAction::triggered, this, [this](){
        QColor color=QColorDialog::getColor(Qt::yellow, this, "Select color");
        if(color.isValid()){
            canvas->selectedColor=color;
            canvas->colorMode=true;
            QPixmap pixmap(":/images/pipette.png");
            pixmap = pixmap.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation); // уменьшаем
            canvas->setCursor(QCursor(pixmap));
        }
    });



}



