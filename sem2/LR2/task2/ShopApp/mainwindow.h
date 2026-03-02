#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QVector>
#include <QComboBox>
#include "product.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent=nullptr);

private slots:
    void switchToCreate();
    void switchToSearch();
    void switchToList();

    void deleteSelectedProduct();
    void saveProductsToFile();
    void loadProductsFromFile();

    void addProduct();
    void searchProduct();
    void showProducts();
    void sortProducts();
    void filterByQuantity();
    void clearFilters();

private:
    QVector<Product> products;

    // Навигационные кнопки (БЕЗ ТЕСТОВ)
    QPushButton *createBtn;
    QPushButton *searchBtn;
    QPushButton *listBtn;
    QStackedWidget *stack;

    // Страница создания товара
    QWidget *createPage;
    QLineEdit *groupEdit;
    QLineEdit *codeEdit;
    QLineEdit *nameEdit;
    QLineEdit *modelEdit;
    QLineEdit *priceEdit;
    QLineEdit *quantityEdit;
    QPushButton *addBtn;
    QLabel *iconLabel;

    // Страница поиска
    QWidget *searchPage;
    QLineEdit *searchNameEdit;
    QLineEdit *searchModelEdit;
    QPushButton *searchBtnPage;
    QTextEdit *searchResult;

    // Страница списка товаров
    QWidget *listPage;
    QPushButton *showAllBtn;
    QPushButton *sortBtn;
    QComboBox *sortFieldCombo;
    QLineEdit *filterQuantityEdit;
    QPushButton *filterBtn;
    QPushButton *deleteBtn;
    QPushButton *saveListBtn;
    QPushButton *loadListBtn;
    QPushButton *clearFilterBtn;
    QTextEdit *listResult;
    QLabel *statsLabel;


    void setupCreatePage();
    void setupSearchPage();
    void setupListPage();
    void applyStyle();
    void updateListDisplay();

};

#endif
