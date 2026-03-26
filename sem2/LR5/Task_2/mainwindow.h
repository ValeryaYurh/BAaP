#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

#include "include/mystring.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void update();

private slots:
    void stringClicked();

private:
    String string;
    QPushButton *stringButton;
    QTextEdit *textEdit;
};

#endif  // MAINWINDOW_H
