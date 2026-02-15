#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    wheel(150, 150, 40, 6)
{
    ui->setupUi(this);

    ui->drawArea->installEventFilter(this);

    connect(&timer, &QTimer::timeout, this, [this]() {
        wheel.rotate(5);
        wheel.move(1, 0);
        ui->drawArea->update();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    timer.start(50);
}

void MainWindow::on_stopButton_clicked()
{
    timer.stop();
}

void MainWindow::on_rotateButton_clicked()
{
    wheel.rotate(20);
    ui->drawArea->update();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->drawArea && event->type() == QEvent::Paint)
    {
        QPainter painter(ui->drawArea);
        painter.setRenderHint(QPainter::Antialiasing);
        wheel.draw(painter);
        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}
