#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include "datestorage.h"
#include "datetests.h"
#include "date.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent=nullptr);
    ~MainWindow();

private:
    DateStorage storage;
    QString currentFile;
    Date currentDate;

    // UI элементы
    QLabel* currentDateLabel;
    QLabel* daysToBirthdayLabel;
    QLineEdit* birthdayInput;
    QPushButton* openBtn;
    QPushButton* addBtn;
    QPushButton* deleteBtn;
    QPushButton* editBtn;
    QPushButton* saveBtn;
    QPushButton* calculateBtn;
    QPushButton* testBtn;
    QPushButton* clearLogBtn;
    QTableWidget* table;
    QTextEdit* logOutput;

    void SetupUI();
    void LoadTable();
    void AddLogMessage(const QString& message);
    void UpdateCurrentDate();
    void UpdateDaysToBirthday();
    int DaysTillBirthday(const Date& date, const Date& birthday);

private slots:
    void OpenFile();
    void AddDate();
    void DeleteDate();
    void EditDate();
    void SaveFile();
    void CalculateDifference();
    void RunTests();
    void OnBirthdayChanged();
    void ClearLog();
};

#endif
