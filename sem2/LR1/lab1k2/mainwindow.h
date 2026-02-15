#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "canvas.h"
#include <QMainWindow>
#include <QAction>

class MainWindow: public QMainWindow
{
    Q_OBJECT
    Canvas *canvas;
public:
    MainWindow(QWidget *parent=nullptr);

};
#endif // MAINWINDOW_H
