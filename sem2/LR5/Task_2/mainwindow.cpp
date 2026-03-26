#include "mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    string(""),
    stringButton(new QPushButton()),
    textEdit(new QTextEdit())
{
    this->setWindowTitle("Task 2");
    this->setStyleSheet(
        "background-color: #181818;"
        "color: white;");
    this->resize(800, 600);

    stringButton->setText("String");

    textEdit->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 10px;"
        "padding: 5px;"
        "font-size: 30px;");
    textEdit->setReadOnly(true);

    // Создаем центральный виджет
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    auto *vLayout = new QVBoxLayout(central);
    vLayout->addWidget(stringButton);
    vLayout->addWidget(textEdit);

    connect(stringButton, &QPushButton::clicked, this, &MainWindow::stringClicked);

    update();
}

MainWindow::~MainWindow()
{
    // Qt автоматически удалит дочерние виджеты
}

void MainWindow::update()
{
    textEdit->setText(QString(string.c_str()));
}

void MainWindow::stringClicked()
{
    auto *dialog = new Dialog(this, &string);
    dialog->exec();
    delete dialog;
}
