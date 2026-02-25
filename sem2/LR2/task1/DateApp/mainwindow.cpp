#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QHeaderView>
#include <QInputDialog>
#include <QApplication>
#include <QDateTime>
#include <QScrollBar>
#include <QDate>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Инициализация всех указателей
    table = nullptr;
    birthdayInput = nullptr;
    openBtn = nullptr;
    addBtn = nullptr;
    deleteBtn = nullptr;
    editBtn = nullptr;
    saveBtn = nullptr;
    calculateBtn = nullptr;
    testBtn = nullptr;
    clearLogBtn = nullptr;
    logOutput = nullptr;
    currentDateLabel = nullptr;
    daysToBirthdayLabel = nullptr;

    // Устанавливаем текущую дату
    QDate today = QDate::currentDate();
    currentDate = Date(today.day(), today.month(), today.year());

    SetupUI();

    // Работа с файлом
    currentFile = QDir::currentPath() + "/dates.txt";

    try {
        storage.CreateDefaultFile(currentFile);
        storage.LoadFromFile(currentFile);
        AddLogMessage("Загружено " + QString::number(storage.GetDates().size()) +
                      " дат из файла: dates.txt");
    } catch (const std::exception& e) {
        AddLogMessage("Ошибка при загрузке файла: " + QString(e.what()));
    }

    UpdateDaysToBirthday();
    LoadTable();
}

MainWindow::~MainWindow()
{
}

void MainWindow::SetupUI()
{
    QWidget* central = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Верхняя панель с текущей датой и днями до ДР
    QHBoxLayout* topPanel = new QHBoxLayout;

    QString currentDateStr = QString("Текущая дата: %1.%2.%3")
                                 .arg(currentDate.GetDay(), 2, 10, QChar('0'))
                                 .arg(currentDate.GetMonth(), 2, 10, QChar('0'))
                                 .arg(currentDate.GetYear());

    currentDateLabel = new QLabel(currentDateStr);
    currentDateLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   color: #1e3c72;"
        "   padding: 8px 15px;"
        "   background: white;"
        "   border: 2px solid #b8d9ff;"
        "   border-radius: 8px;"
        "}"
        );

    daysToBirthdayLabel = new QLabel("Дней до ДР: --");
    daysToBirthdayLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   color: #ff6b6b;"
        "   padding: 8px 15px;"
        "   background: white;"
        "   border: 2px solid #ffb8b8;"
        "   border-radius: 8px;"
        "   margin-left: 10px;"
        "}"
        );

    topPanel->addWidget(currentDateLabel);
    topPanel->addWidget(daysToBirthdayLabel);
    topPanel->addStretch();

    // Панель с днем рождения
    QHBoxLayout* birthdayPanel = new QHBoxLayout;

    QLabel* birthdayLabel = new QLabel("Дата рождения (дд.мм.гггг):");
    birthdayLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #1e3c72;");

    birthdayInput = new QLineEdit;
    birthdayInput->setPlaceholderText("15.08.2008");
    birthdayInput->setMinimumHeight(35);
    birthdayInput->setMaximumWidth(200);

    birthdayPanel->addWidget(birthdayLabel);
    birthdayPanel->addWidget(birthdayInput);
    birthdayPanel->addStretch();

    // Панель с кнопками
    QHBoxLayout* buttonPanel = new QHBoxLayout;
    buttonPanel->setSpacing(10);

    openBtn = new QPushButton("📂 Открыть файл");
    addBtn = new QPushButton("➕ Добавить дату");
    deleteBtn = new QPushButton("🗑️ Удалить");
    editBtn = new QPushButton("✏️ Редактировать");
    saveBtn = new QPushButton("💾 Сохранить");
    calculateBtn = new QPushButton("📊 Вычислить");
    testBtn = new QPushButton("🧪 Тестирование");

    buttonPanel->addWidget(openBtn);
    buttonPanel->addWidget(addBtn);
    buttonPanel->addWidget(deleteBtn);
    buttonPanel->addWidget(editBtn);
    buttonPanel->addWidget(saveBtn);
    buttonPanel->addWidget(calculateBtn);
    buttonPanel->addWidget(testBtn);
    buttonPanel->addStretch();

    // Таблица с датами (7 колонок)
    table = new QTableWidget;
    table->setColumnCount(7);
    QStringList headers = {
        "Дата",
        "Следующий день",
        "Предыдущий день",
        "Високосный",
        "Неделя",
        "Разница со след.",
        "Дней до ДР"
    };
    table->setHorizontalHeaderLabels(headers);
    table->setAlternatingRowColors(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Настройка размеров столбцов
    QHeaderView* header = table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Interactive);
    header->setStretchLastSection(false);
    header->setMinimumSectionSize(80);
    header->setSectionsMovable(true);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 120);
    table->setColumnWidth(2, 120);
    table->setColumnWidth(3, 90);
    table->setColumnWidth(4, 70);
    table->setColumnWidth(5, 110);
    table->setColumnWidth(6, 100);

    // Панель для лога с кнопкой очистки
    QHBoxLayout* logPanel = new QHBoxLayout;

    QLabel* logLabel = new QLabel("📋 Лог событий:");
    logLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #1e3c72;");

    clearLogBtn = new QPushButton("🧹 Очистить лог");
    clearLogBtn->setMaximumWidth(120);
    clearLogBtn->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "       stop:0 #6c757d, stop:1 #495057);"
        "   color: white;"
        "   font-size: 11px;"
        "   padding: 4px 8px;"
        "   border-radius: 10px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "       stop:0 #7c858d, stop:1 #5a6268);"
        "}"
        );

    logPanel->addWidget(logLabel);
    logPanel->addStretch();
    logPanel->addWidget(clearLogBtn);

    // Лог событий
    logOutput = new QTextEdit;
    logOutput->setReadOnly(true);
    logOutput->setMinimumHeight(150);
    logOutput->setMaximumHeight(200);

    QFont logFont("Courier New", 10);
    logFont.setStyleHint(QFont::Monospace);
    logOutput->setFont(logFont);

    logOutput->setStyleSheet(
        "QTextEdit {"
        "   background-color: #1e1e2e;"
        "   color: #cdd6f4;"
        "   border: 2px solid #89b4fa;"
        "   border-radius: 8px;"
        "   padding: 10px;"
        "   font-family: 'Courier New', monospace;"
        "}"
        "QScrollBar:vertical {"
        "   background-color: #313244;"
        "   width: 14px;"
        "   border-radius: 7px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background-color: #585b70;"
        "   border-radius: 7px;"
        "   min-height: 30px;"
        "}"
        );

    // Собираем всё вместе
    mainLayout->addLayout(topPanel);
    mainLayout->addLayout(birthdayPanel);
    mainLayout->addLayout(buttonPanel);
    mainLayout->addWidget(table);
    mainLayout->addLayout(logPanel);
    mainLayout->addWidget(logOutput);

    central->setLayout(mainLayout);
    setCentralWidget(central);

    // Стиль для всего окна
    setStyleSheet(
        "QMainWindow {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #f0f9ff, stop:1 #e6f2fa);"
        "}"
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "       stop:0 #6eb5ff, stop:1 #4a8fe0);"
        "   color: white;"
        "   font-size: 12px;"
        "   font-weight: bold;"
        "   padding: 6px 12px;"
        "   border-radius: 15px;"
        "   border: none;"
        "   min-width: 90px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "       stop:0 #7ec5ff, stop:1 #5a9ff0);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "       stop:0 #3a7fd0, stop:1 #2a6fc0);"
        "}"
        "QPushButton#deleteBtn {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "       stop:0 #ff6b6b, stop:1 #ee5253);"
        "}"
        "QPushButton#testBtn {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "       stop:0 #9c27b0, stop:1 #7b1fa2);"
        "}"
        "QLineEdit {"
        "   padding: 6px 12px;"
        "   font-size: 13px;"
        "   border: 2px solid #b8d9ff;"
        "   border-radius: 20px;"
        "   background-color: white;"
        "}"
        "QTableWidget {"
        "   background-color: white;"
        "   alternate-background-color: #f8fcff;"
        "   gridline-color: #d0e0f0;"
        "   font-size: 12px;"
        "   border: 2px solid #b8d9ff;"
        "   border-radius: 8px;"
        "}"
        "QHeaderView::section {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "       stop:0 #e6f0fa, stop:1 #d0e4f5);"
        "   color: #1e3c72;"
        "   padding: 8px;"
        "   border: none;"
        "   font-weight: bold;"
        "}"
        );

    deleteBtn->setObjectName("deleteBtn");
    testBtn->setObjectName("testBtn");

    // Подключаем сигналы
    connect(openBtn, &QPushButton::clicked, this, &MainWindow::OpenFile);
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::AddDate);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::DeleteDate);
    connect(editBtn, &QPushButton::clicked, this, &MainWindow::EditDate);
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::SaveFile);
    connect(calculateBtn, &QPushButton::clicked, this, &MainWindow::CalculateDifference);
    connect(testBtn, &QPushButton::clicked, this, &MainWindow::RunTests);
    connect(birthdayInput, &QLineEdit::textChanged, this, &MainWindow::OnBirthdayChanged);
    connect(clearLogBtn, &QPushButton::clicked, this, &MainWindow::ClearLog);
}

// ==== НОВЫЕ МЕТОДЫ, КОТОРЫХ НЕ ХВАТАЛО ====

void MainWindow::AddLogMessage(const QString& message)
{
    if (!logOutput) return;

    QString timestamp = QDateTime::currentDateTime().toString("[hh:mm:ss]");
    QString logEntry = timestamp + " " + message;

    QString currentText = logOutput->toPlainText();
    logOutput->setPlainText(logEntry + "\n" + currentText);
}

int MainWindow::DaysTillBirthday(const Date& date, const Date& birthday)
{
    Date nextBirthday(birthday.GetDay(), birthday.GetMonth(), date.GetYear());

    if (date.Duration(nextBirthday) < 0) {
        nextBirthday = Date(birthday.GetDay(), birthday.GetMonth(), date.GetYear() + 1);
    }

    return abs(date.Duration(nextBirthday));
}

void MainWindow::UpdateDaysToBirthday()
{
    if (!daysToBirthdayLabel) return;

    try {
        Date birthday(15, 8, 2008);
        QString birthdayText = birthdayInput->text().trimmed();

        if (!birthdayText.isEmpty()) {
            QStringList parts = birthdayText.split(".");
            if (parts.size() == 3) {
                birthday = Date(parts[0].toInt(), parts[1].toInt(), parts[2].toInt());
            }
        }

        int daysToBday = DaysTillBirthday(currentDate, birthday);
        daysToBirthdayLabel->setText("Дней до ДР: " + QString::number(daysToBday));

        if (daysToBday <= 7) {
            daysToBirthdayLabel->setStyleSheet(
                "QLabel {"
                "   font-size: 16px;"
                "   font-weight: bold;"
                "   color: white;"
                "   padding: 8px 15px;"
                "   background: #ff4444;"
                "   border: 2px solid #ff8888;"
                "   border-radius: 8px;"
                "   margin-left: 10px;"
                "}"
                );
        } else if (daysToBday <= 30) {
            daysToBirthdayLabel->setStyleSheet(
                "QLabel {"
                "   font-size: 16px;"
                "   font-weight: bold;"
                "   color: #ff8c00;"
                "   padding: 8px 15px;"
                "   background: white;"
                "   border: 2px solid #ffb84d;"
                "   border-radius: 8px;"
                "   margin-left: 10px;"
                "}"
                );
        } else {
            daysToBirthdayLabel->setStyleSheet(
                "QLabel {"
                "   font-size: 16px;"
                "   font-weight: bold;"
                "   color: #ff6b6b;"
                "   padding: 8px 15px;"
                "   background: white;"
                "   border: 2px solid #ffb8b8;"
                "   border-radius: 8px;"
                "   margin-left: 10px;"
                "}"
                );
        }

    } catch (const std::exception& e) {
        daysToBirthdayLabel->setText("Дней до ДР: ошибка");
    }
}

void MainWindow::UpdateCurrentDate()
{
    QDate today = QDate::currentDate();
    currentDate = Date(today.day(), today.month(), today.year());

    QString currentDateStr = QString("Текущая дата: %1.%2.%3")
                                 .arg(currentDate.GetDay(), 2, 10, QChar('0'))
                                 .arg(currentDate.GetMonth(), 2, 10, QChar('0'))
                                 .arg(currentDate.GetYear());

    if (currentDateLabel) {
        currentDateLabel->setText(currentDateStr);
    }

    UpdateDaysToBirthday();
}

void MainWindow::ClearLog()
{
    if (!logOutput) return;

    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Очистка лога",
                                                              "Очистить историю событий?",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        logOutput->clear();
        AddLogMessage("🧹 Лог событий очищен");
    }
}

// ==== ОСТАЛЬНЫЕ МЕТОДЫ (LoadTable, OpenFile, AddDate и т.д.) ====

void MainWindow::LoadTable()
{
    if (!table) return;

    try {
        const auto& dates = storage.GetDates();
        table->setRowCount(dates.size());

        Date birthday(15, 8, 2008);
        QString birthdayText = birthdayInput->text().trimmed();
        if (!birthdayText.isEmpty()) {
            QStringList parts = birthdayText.split(".");
            if (parts.size() == 3) {
                birthday = Date(parts[0].toInt(), parts[1].toInt(), parts[2].toInt());
            }
        }

        for (int i = 0; i < dates.size(); ++i) {
            try {
                const Date& currentDate = dates[i];

                QString dateStr = QString("%1.%2.%3")
                                      .arg(currentDate.GetDay(), 2, 10, QChar('0'))
                                      .arg(currentDate.GetMonth(), 2, 10, QChar('0'))
                                      .arg(currentDate.GetYear());

                Date nextDay = currentDate.NextDay();
                QString nextStr = QString("%1.%2.%3")
                                      .arg(nextDay.GetDay(), 2, 10, QChar('0'))
                                      .arg(nextDay.GetMonth(), 2, 10, QChar('0'))
                                      .arg(nextDay.GetYear());

                Date prevDay = currentDate.PreviousDay();
                QString prevStr = QString("%1.%2.%3")
                                      .arg(prevDay.GetDay(), 2, 10, QChar('0'))
                                      .arg(prevDay.GetMonth(), 2, 10, QChar('0'))
                                      .arg(prevDay.GetYear());

                QString leapStr = currentDate.IsLeap() ? "Да" : "Нет";
                int weekNum = currentDate.WeekNumber();
                int daysToBday = DaysTillBirthday(currentDate, birthday);

                table->setItem(i, 0, new QTableWidgetItem(dateStr));
                table->setItem(i, 1, new QTableWidgetItem(nextStr));
                table->setItem(i, 2, new QTableWidgetItem(prevStr));

                QTableWidgetItem* leapItem = new QTableWidgetItem(leapStr);
                leapItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(i, 3, leapItem);

                QTableWidgetItem* weekItem = new QTableWidgetItem(QString::number(weekNum));
                weekItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(i, 4, weekItem);

                if (i + 1 < dates.size()) {
                    int diff = currentDate.Duration(dates[i + 1]);
                    diff = abs(diff);
                    QTableWidgetItem* diffItem = new QTableWidgetItem(QString::number(diff));
                    diffItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
                    table->setItem(i, 5, diffItem);
                } else {
                    QTableWidgetItem* diffItem = new QTableWidgetItem("-");
                    diffItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(i, 5, diffItem);
                }

                QTableWidgetItem* bdayItem = new QTableWidgetItem(QString::number(daysToBday));
                bdayItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
                table->setItem(i, 6, bdayItem);

            } catch (const std::exception& e) {
                for (int col = 0; col < 7; ++col) {
                    table->setItem(i, col, new QTableWidgetItem("ERR"));
                }
            }
        }

        table->resizeColumnsToContents();
        AddLogMessage("Таблица обновлена. Загружено " + QString::number(dates.size()) + " дат");

    } catch (const std::exception& e) {
        AddLogMessage("Ошибка загрузки таблицы: " + QString(e.what()));
    }
}

void MainWindow::OnBirthdayChanged()
{
    UpdateDaysToBirthday();
    LoadTable();
    AddLogMessage("День рождения изменен: " + birthdayInput->text());
}

void MainWindow::OpenFile()
{
    QString file = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Text files (*.txt)");
    if (file.isEmpty()) return;

    try {
        currentFile = file;
        storage.LoadFromFile(currentFile);
        LoadTable();
        AddLogMessage("Открыт файл: " + QFileInfo(file).fileName());
    } catch (const std::exception& e) {
        AddLogMessage("Ошибка при открытии файла: " + QString(e.what()));
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void MainWindow::AddDate()
{
    bool ok;
    QString text = QInputDialog::getText(this, "Добавить дату",
                                         "Введите дату в формате ДД.ММ.ГГГГ:",
                                         QLineEdit::Normal, "", &ok);

    if (!ok || text.isEmpty()) return;

    QStringList parts = text.split(".");
    if (parts.size() != 3) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат. Используйте ДД.ММ.ГГГГ");
        return;
    }

    bool ok1, ok2, ok3;
    int day = parts[0].toInt(&ok1);
    int month = parts[1].toInt(&ok2);
    int year = parts[2].toInt(&ok3);

    if (!ok1 || !ok2 || !ok3) {
        QMessageBox::warning(this, "Ошибка", "Дата должна содержать только цифры");
        return;
    }

    try {
        Date newDate(day, month, year);
        storage.AppendToFile(currentFile, newDate);
        storage.LoadFromFile(currentFile);
        LoadTable();
        AddLogMessage("Добавлена дата: " + text);
    } catch (const std::exception& e) {
        AddLogMessage("Ошибка при добавлении даты: " + QString(e.what()));
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void MainWindow::DeleteDate()
{
    if (!table) return;

    int currentRow = table->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Предупреждение",
                             "Сначала выберите дату для удаления");
        return;
    }

    const auto& dates = storage.GetDates();
    if (currentRow >= dates.size()) return;

    const Date& selectedDate = dates[currentRow];
    QString dateStr = QString("%1.%2.%3")
                          .arg(selectedDate.GetDay(), 2, 10, QChar('0'))
                          .arg(selectedDate.GetMonth(), 2, 10, QChar('0'))
                          .arg(selectedDate.GetYear());

    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Подтверждение удаления",
                                                              "Удалить дату: " + dateStr + "?",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply != QMessageBox::Yes) return;

    try {
        std::vector<Date> newDates;
        for (size_t i = 0; i < dates.size(); ++i) {
            if (i != currentRow) {
                newDates.push_back(dates[i]);
            }
        }

        storage.SetDates(newDates);
        storage.SaveToFile(currentFile);
        LoadTable();

        AddLogMessage("Удалена дата: " + dateStr);

    } catch (const std::exception& e) {
        AddLogMessage("Ошибка при удалении: " + QString(e.what()));
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void MainWindow::EditDate()
{
    if (!table) return;

    int currentRow = table->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Предупреждение",
                             "Сначала выберите дату для редактирования");
        return;
    }

    const auto& dates = storage.GetDates();
    if (currentRow >= dates.size()) return;

    const Date& selectedDate = dates[currentRow];
    QString currentDateStr = QString("%1.%2.%3")
                                 .arg(selectedDate.GetDay(), 2, 10, QChar('0'))
                                 .arg(selectedDate.GetMonth(), 2, 10, QChar('0'))
                                 .arg(selectedDate.GetYear());

    bool ok;
    QString text = QInputDialog::getText(this, "Редактировать дату",
                                         "Измените дату (ДД.ММ.ГГГГ):",
                                         QLineEdit::Normal, currentDateStr, &ok);

    if (!ok || text.isEmpty()) return;

    QStringList parts = text.split(".");
    if (parts.size() != 3) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат");
        return;
    }

    try {
        Date newDate(parts[0].toInt(), parts[1].toInt(), parts[2].toInt());

        std::vector<Date> newDates = dates;
        newDates[currentRow] = newDate;

        storage.SetDates(newDates);
        storage.SaveToFile(currentFile);
        LoadTable();

        AddLogMessage("Отредактирована дата: " + currentDateStr + " -> " + text);

    } catch (const std::exception& e) {
        AddLogMessage("Ошибка при редактировании: " + QString(e.what()));
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void MainWindow::SaveFile()
{
    try {
        storage.SaveToFile(currentFile);
        AddLogMessage("Файл сохранен: " + QFileInfo(currentFile).fileName());
    } catch (const std::exception& e) {
        AddLogMessage("Ошибка при сохранении: " + QString(e.what()));
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void MainWindow::CalculateDifference()
{
    const auto& dates = storage.GetDates();

    if (dates.size() < 2) {
        QMessageBox::information(this, "Информация",
                                 "Нужно минимум 2 даты для расчета разницы");
        return;
    }

    QStringList items;
    for (size_t i = 0; i < dates.size(); ++i) {
        items << QString("%1. %2.%3.%4")
        .arg(i + 1)
            .arg(dates[i].GetDay(), 2, 10, QChar('0'))
            .arg(dates[i].GetMonth(), 2, 10, QChar('0'))
            .arg(dates[i].GetYear());
    }

    bool ok1, ok2;
    QString item1 = QInputDialog::getItem(this, "Выберите первую дату",
                                          "Первая дата:", items, 0, false, &ok1);

    if (!ok1) return;

    QString item2 = QInputDialog::getItem(this, "Выберите вторую дату",
                                          "Вторая дата:", items, 1, false, &ok2);

    if (!ok2) return;

    int index1 = items.indexOf(item1);
    int index2 = items.indexOf(item2);

    if (index1 >= 0 && index2 >= 0) {
        try {
            int diff = dates[index1].Duration(dates[index2]);
            diff = abs(diff);

            QString message = QString("Разница между датами:\n\n"
                                      "Дата 1: %1\n"
                                      "Дата 2: %2\n\n"
                                      "Количество дней: %3")
                                  .arg(item1.mid(3))
                                  .arg(item2.mid(3))
                                  .arg(diff);

            AddLogMessage("Вычислена разница: " + QString::number(diff) + " дней");
            QMessageBox::information(this, "Результат", message);

        } catch (const std::exception& e) {
            AddLogMessage("Ошибка при вычислении: " + QString(e.what()));
            QMessageBox::warning(this, "Ошибка", e.what());
        }
    }
}

void MainWindow::RunTests()
{
    AddLogMessage("🔄 Запуск тестов...");
    QApplication::processEvents();

    try {
        QString result = DateTests::RunAllTests();
        AddLogMessage("✅ Тесты завершены:\n" + result);
    } catch (const std::exception& e) {
        AddLogMessage("❌ Ошибка тестов: " + QString(e.what()));
    }
}
