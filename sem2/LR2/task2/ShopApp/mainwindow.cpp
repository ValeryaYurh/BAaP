#include "mainwindow.h"
#include "agevalidator.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QTextStream>
#include <QFile>
#include <QFont>
#include <QGroupBox>
#include <QScrollArea>
#include <QDateTime>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *central = new QWidget;
    setCentralWidget(central);

    // Создаем навигационные кнопки с иконками
    createBtn = new QPushButton("📦 Создать товар");
    searchBtn = new QPushButton("🔍 Поиск товара");
    listBtn = new QPushButton("📋 Список товаров");

    // Устанавливаем фиксированную высоту для кнопок
    QList<QPushButton*> navButtons = {createBtn, searchBtn, listBtn};
    for(auto btn : navButtons) {
        btn->setMinimumHeight(40);
        btn->setCursor(Qt::PointingHandCursor);
    }

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setSpacing(10);
    topLayout->addWidget(createBtn);
    topLayout->addWidget(searchBtn);
    topLayout->addWidget(listBtn);
    topLayout->addStretch();

    stack = new QStackedWidget;
    stack->setContentsMargins(10, 10, 10, 10);

    setupCreatePage();
    setupSearchPage();
    setupListPage();

    stack->addWidget(createPage);
    stack->addWidget(searchPage);
    stack->addWidget(listPage);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(15);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(stack);

    central->setLayout(mainLayout);

    // Навигация
    connect(createBtn, &QPushButton::clicked, this, &MainWindow::switchToCreate);
    connect(searchBtn, &QPushButton::clicked, this, &MainWindow::switchToSearch);
    connect(listBtn, &QPushButton::clicked, this, &MainWindow::switchToList);

    // Действия
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::addProduct);
    connect(searchBtnPage, &QPushButton::clicked, this, &MainWindow::searchProduct);
    connect(showAllBtn, &QPushButton::clicked, this, &MainWindow::showProducts);
    connect(sortBtn, &QPushButton::clicked, this, &MainWindow::sortProducts);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteSelectedProduct);
    connect(filterBtn, &QPushButton::clicked, this, &MainWindow::filterByQuantity);
    connect(clearFilterBtn, &QPushButton::clicked, this, &MainWindow::clearFilters);
    connect(saveListBtn, &QPushButton::clicked, this, &MainWindow::saveProductsToFile);
    connect(loadListBtn, &QPushButton::clicked, this, &MainWindow::loadProductsFromFile);

    applyStyle();
    switchToCreate();
    runBlackBoxTests();
}

// ----------------- Страница создания товара -----------------
void MainWindow::setupCreatePage()
{
    createPage = new QWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(15);

    // Заголовок
    QLabel *title = new QLabel("➕ Добавление нового товара");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: #2c3e50; margin-bottom: 10px;");
    title->setAlignment(Qt::AlignCenter);

    // Иконка категории (эмоджи) с фоном
    QWidget *iconContainer = new QWidget;
    iconContainer->setFixedHeight(100);
    iconContainer->setStyleSheet("background-color: #f0f8ff; border-radius: 50px;");

    QHBoxLayout *iconLayout = new QHBoxLayout(iconContainer);
    iconLabel = new QLabel("📦");
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setStyleSheet("font-size: 64px; background: transparent;");
    iconLayout->addWidget(iconLabel);

    // Группа полей ввода
    QGroupBox *inputGroup = new QGroupBox("Информация о товаре");
    inputGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #b0c4de; border-radius: 8px; margin-top: 10px; padding-top: 10px; }");

    QGridLayout *gridLayout = new QGridLayout(inputGroup);
    gridLayout->setVerticalSpacing(12);
    gridLayout->setHorizontalSpacing(15);

    // Создаем поля ввода
    groupEdit = new QLineEdit;
    codeEdit = new QLineEdit;
    nameEdit = new QLineEdit;
    modelEdit = new QLineEdit;
    priceEdit = new QLineEdit;
    quantityEdit = new QLineEdit;

    // Валидаторы
    priceEdit->setValidator(new QDoubleValidator(0, 999999, 2, this));
    quantityEdit->setValidator(new QIntValidator(0, 99999, this));

    // Добавляем подсказки
    groupEdit->setPlaceholderText("Например: Фрукты, Овощи, Мясо, Молоко, Хлеб");
    codeEdit->setPlaceholderText("Артикул товара");
    nameEdit->setPlaceholderText("Наименование");
    modelEdit->setPlaceholderText("Модель");
    priceEdit->setPlaceholderText("0.00");
    quantityEdit->setPlaceholderText("0");

    // Расставляем поля по сетке
    gridLayout->addWidget(new QLabel("📁 Группа:"), 0, 0);
    gridLayout->addWidget(groupEdit, 0, 1);
    gridLayout->addWidget(new QLabel("🏷️ Код:"), 1, 0);
    gridLayout->addWidget(codeEdit, 1, 1);
    gridLayout->addWidget(new QLabel("📝 Название:"), 2, 0);
    gridLayout->addWidget(nameEdit, 2, 1);
    gridLayout->addWidget(new QLabel("🔧 Модель:"), 3, 0);
    gridLayout->addWidget(modelEdit, 3, 1);
    gridLayout->addWidget(new QLabel("💰 Цена:"), 4, 0);
    gridLayout->addWidget(priceEdit, 4, 1);
    gridLayout->addWidget(new QLabel("📊 Количество:"), 5, 0);
    gridLayout->addWidget(quantityEdit, 5, 1);

    // Кнопка добавления
    addBtn = new QPushButton("✅ Добавить товар");
    addBtn->setMinimumHeight(45);
    addBtn->setCursor(Qt::PointingHandCursor);
    addBtn->setStyleSheet("QPushButton { font-size: 14px; }");

    // Собираем все вместе
    mainLayout->addWidget(title);
    mainLayout->addWidget(iconContainer);
    mainLayout->addWidget(inputGroup);
    mainLayout->addWidget(addBtn);
    mainLayout->addStretch();

    createPage->setLayout(mainLayout);

    // Меняем эмоджи в зависимости от группы
    connect(groupEdit, &QLineEdit::textChanged, this, [this](const QString &text){
        QString t = text.toLower();
        if(t.contains("фрукт") || t.contains("яблоко") || t.contains("банан") || t.contains("апельсин"))
            iconLabel->setText("🍎");
        else if(t.contains("овощ") || t.contains("морковь") || t.contains("картош") || t.contains("помидор"))
            iconLabel->setText("🥕");
        else if(t.contains("мясо") || t.contains("стейк") || t.contains("куриц") || t.contains("говяд"))
            iconLabel->setText("🥩");
        else if(t.contains("молочн") || t.contains("молоко") || t.contains("сыр") || t.contains("йогурт"))
            iconLabel->setText("🥛");
        else if(t.contains("напит") || t.contains("вода") || t.contains("сок") || t.contains("кола"))
            iconLabel->setText("🧃");
        else if(t.contains("хлеб") || t.contains("булк") || t.contains("печень") || t.contains("торт") || t.contains("пирож"))
            iconLabel->setText("🍞");
        else
            iconLabel->setText("📦");
    });
}

// ----------------- Страница поиска -----------------
void MainWindow::setupSearchPage()
{
    searchPage = new QWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(15);

    QLabel *title = new QLabel("🔎 Поиск товаров");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: #2c3e50;");
    title->setAlignment(Qt::AlignCenter);

    QGroupBox *searchGroup = new QGroupBox("Критерии поиска");
    searchGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #b0c4de; border-radius: 8px; }");

    QGridLayout *gridLayout = new QGridLayout(searchGroup);

    searchNameEdit = new QLineEdit;
    searchModelEdit = new QLineEdit;
    searchNameEdit->setPlaceholderText("Введите название");
    searchModelEdit->setPlaceholderText("Введите модель");

    gridLayout->addWidget(new QLabel("📝 Название:"), 0, 0);
    gridLayout->addWidget(searchNameEdit, 0, 1);
    gridLayout->addWidget(new QLabel("🔧 Модель:"), 1, 0);
    gridLayout->addWidget(searchModelEdit, 1, 1);

    searchBtnPage = new QPushButton("🔍 Найти");
    searchBtnPage->setMinimumHeight(40);
    searchBtnPage->setCursor(Qt::PointingHandCursor);

    searchResult = new QTextEdit;
    searchResult->setReadOnly(true);
    searchResult->setMinimumHeight(200);
    searchResult->setFont(QFont("Consolas", 10));

    mainLayout->addWidget(title);
    mainLayout->addWidget(searchGroup);
    mainLayout->addWidget(searchBtnPage);
    mainLayout->addWidget(new QLabel("Результаты поиска:"));
    mainLayout->addWidget(searchResult);

    searchPage->setLayout(mainLayout);
}

// ----------------- Страница списка товаров -----------------
void MainWindow::setupListPage()
{
    listPage = new QWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(15);

    QLabel *title = new QLabel("📋 Управление товарами");
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: #2c3e50;");
    title->setAlignment(Qt::AlignCenter);

    // Панель инструментов
    QHBoxLayout *toolbarLayout = new QHBoxLayout;

    showAllBtn = new QPushButton("🔄 Показать все");
    sortBtn = new QPushButton("📊 Сортировать");
    deleteBtn = new QPushButton("🗑️ Удалить");
    saveListBtn = new QPushButton("💾 Сохранить список");
    loadListBtn = new QPushButton("📂 Загрузить список");

    sortFieldCombo = new QComboBox;
    sortFieldCombo->addItems({"Код товара", "Наименование", "Цена", "Количество"});

    toolbarLayout->addWidget(showAllBtn);
    toolbarLayout->addWidget(sortBtn);
    toolbarLayout->addWidget(deleteBtn);
    toolbarLayout->addWidget(saveListBtn);    // Добавляем
    toolbarLayout->addWidget(loadListBtn);    // Добавляем
    toolbarLayout->addWidget(new QLabel("Сортировать по:"));
    toolbarLayout->addWidget(sortFieldCombo);
    toolbarLayout->addStretch();

    // Панель фильтрации
    QHBoxLayout *filterLayout = new QHBoxLayout;

    filterQuantityEdit = new QLineEdit;
    filterQuantityEdit->setPlaceholderText("Меньше чем...");
    filterQuantityEdit->setValidator(new QIntValidator(0, 99999, this));
    filterQuantityEdit->setMaximumWidth(150);

    filterBtn = new QPushButton("🔍 Фильтр");
    clearFilterBtn = new QPushButton("❌ Сброс");

    filterLayout->addWidget(new QLabel("Товаров меньше:"));
    filterLayout->addWidget(filterQuantityEdit);
    filterLayout->addWidget(filterBtn);
    filterLayout->addWidget(clearFilterBtn);
    filterLayout->addStretch();

    // Статистика
    statsLabel = new QLabel("Всего товаров: 0 | Отображается: 0 | На складе: 0 шт. | Общая сумма: 0 руб.");
    statsLabel->setStyleSheet("font-weight: bold; color: #2c3e50; padding: 5px;");

    // Результат
    listResult = new QTextEdit;
    listResult->setReadOnly(true);
    listResult->setMinimumHeight(250);
    listResult->setFont(QFont("Consolas", 10));

    mainLayout->addWidget(title);
    mainLayout->addLayout(toolbarLayout);
    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(statsLabel);
    mainLayout->addWidget(listResult);

    listPage->setLayout(mainLayout);
}

// ----------------- Навигация -----------------
void MainWindow::switchToCreate() { stack->setCurrentWidget(createPage); }
void MainWindow::switchToSearch() { stack->setCurrentWidget(searchPage); }
void MainWindow::switchToList()
{
    stack->setCurrentWidget(listPage);
    updateListDisplay();
}

// ----------------- Логика работы с товарами -----------------
void MainWindow::deleteSelectedProduct()
{
    // Получаем текущий текст
    QString allText = listResult->toPlainText();
    QStringList lines = allText.split('\n');

    // Получаем позицию курсора
    QTextCursor cursor = listResult->textCursor();
    int cursorPosition = cursor.position();

    // Находим строку, на которой стоит курсор
    int selectedLineIndex = -1;
    int currentPos = 0;

    for (int i = 0; i < lines.size(); i++) {
        int lineLength = lines[i].length() + 1; // +1 для символа новой строки
        if (cursorPosition >= currentPos && cursorPosition <= currentPos + lineLength) {
            selectedLineIndex = i;
            break;
        }
        currentPos += lineLength;
    }

    qDebug() << "Выбрана строка с индексом:" << selectedLineIndex;

    // Проверяем, что выбрана корректная строка
    if (selectedLineIndex <= 2) {
        QMessageBox::warning(this, "Ошибка",
                             "Пожалуйста, кликните на строку с товаром (не на заголовок)");
        return;
    }

    if (selectedLineIndex >= lines.size() - 2) {
        QMessageBox::warning(this, "Ошибка",
                             "Пожалуйста, кликните на строку с товаром (не на итоговую строку)");
        return;
    }

    // Получаем выбранную строку и разбираем её
    QString selectedLine = lines[selectedLineIndex].trimmed();
    qDebug() << "Выбранная строка:" << selectedLine;

    // Разбираем строку по пробелам и символу |
    // Сначала заменяем множественные пробелы на один
    QString cleaned = selectedLine.simplified();

    // Ищем части, разделенные |
    QStringList parts;
    QString current;
    bool inPart = false;

    for (int i = 0; i < cleaned.length(); i++) {
        QChar ch = cleaned[i];
        if (ch == '|') {
            if (!current.trimmed().isEmpty()) {
                parts.append(current.trimmed());
            }
            current.clear();
            inPart = true;
        } else {
            current += ch;
        }
    }
    if (!current.trimmed().isEmpty()) {
        parts.append(current.trimmed());
    }

    qDebug() << "Разобрано частей:" << parts.size();
    for (int i = 0; i < parts.size(); i++) {
        qDebug() << "  [" << i << "] = '" << parts[i] << "'";
    }

    // Теперь ищем код товара (он должен быть где-то в строке)
    QString foundCode;
    QString foundName;
    QString foundModel;

    // Перебираем все части и ищем похожее на код (цифры)
    for (const QString& part : parts) {
        QString trimmed = part.trimmed();
        if (trimmed.isEmpty()) continue;

        // Проверяем, состоит ли часть только из цифр (это может быть код)
        bool isDigits = true;
        for (QChar ch : trimmed) {
            if (!ch.isDigit()) {
                isDigits = false;
                break;
            }
        }

        if (isDigits && trimmed.length() >= 3) {
            foundCode = trimmed;
            qDebug() << "Найден возможный код:" << foundCode;
        }

        // Также сохраняем возможные название и модель
        if (trimmed.length() > 2 && !trimmed.contains('.')) {
            if (foundName.isEmpty()) {
                foundName = trimmed;
            } else if (foundModel.isEmpty()) {
                foundModel = trimmed;
            }
        }
    }

    qDebug() << "Ищем товар: код=" << foundCode << ", название=" << foundName << ", модель=" << foundModel;

    if (foundCode.isEmpty()) {
        QMessageBox::warning(this, "Ошибка",
                             "Не удалось определить код товара. Пожалуйста, кликните на строку с товаром.");
        return;
    }

    // Ищем товар в векторе
    int indexToDelete = -1;
    for (int i = 0; i < products.size(); i++) {
        const Product& p = products[i];

        // Сравниваем по коду (самый надежный способ)
        if (p.code.trimmed() == foundCode) {
            indexToDelete = i;
            qDebug() << "Найден товар по коду! Индекс:" << i;
            break;
        }

        // Если код не совпал, пробуем по названию и модели
        if (!foundName.isEmpty() && !foundModel.isEmpty()) {
            if (p.name.trimmed() == foundName && p.model.trimmed() == foundModel) {
                indexToDelete = i;
                qDebug() << "Найден товар по названию и модели! Индекс:" << i;
                break;
            }
        }
    }

    if (indexToDelete == -1) {
        qDebug() << "ТОВАР НЕ НАЙДЕН!";

        // Показываем все доступные товары для отладки
        QString debugInfo = "Доступные товары:\n";
        for (int i = 0; i < products.size(); i++) {
            debugInfo += QString("  %1: %2 - %3 %4\n")
            .arg(i)
                .arg(products[i].code)
                .arg(products[i].name)
                .arg(products[i].model);
        }

        QMessageBox::warning(this, "Ошибка",
                             "Товар не найден в базе данных.\n\n"
                             "Искали код: " + foundCode + "\n\n" + debugInfo);
        return;
    }

    // Подтверждение удаления
    const Product& p = products[indexToDelete];
    QString productInfo = QString("Код: %1\nНазвание: %2\nМодель: %3\nГруппа: %4\nЦена: %5 руб.\nКоличество: %6")
                              .arg(p.code)
                              .arg(p.name)
                              .arg(p.model)
                              .arg(p.group)
                              .arg(p.price, 0, 'f', 2)
                              .arg(p.quantity);

    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Подтверждение удаления",
                                                              "Вы действительно хотите удалить этот товар?\n\n" + productInfo,
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply != QMessageBox::Yes) return;

    // Удаляем товар
    products.removeAt(indexToDelete);
    qDebug() << "Товар удален. Осталось товаров:" << products.size();

    // Обновляем отображение
    updateListDisplay();
}

void MainWindow::addProduct()
{
    // Проверка заполнения полей
    if (groupEdit->text().isEmpty() || codeEdit->text().isEmpty() ||
        nameEdit->text().isEmpty() || modelEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля!");
        return;
    }

    // Обработка цены - УЛУЧШЕННАЯ ВЕРСИЯ
    QString priceText = priceEdit->text().trimmed();

    // Если поле цены пустое, устанавливаем 0
    if (priceText.isEmpty()) {
        priceText = "0";
    }

    // Заменяем запятую на точку для корректного преобразования
    priceText.replace(',', '.');

    bool priceOk;
    double price = priceText.toDouble(&priceOk);

    if (!priceOk) {
        QMessageBox::warning(this, "Ошибка",
                             "Некорректная цена! Введите число (например: 10.50 или 10,50)");
        priceEdit->setFocus();
        return;
    }

    if (price < 0) {
        QMessageBox::warning(this, "Ошибка", "Цена не может быть отрицательной!");
        priceEdit->setFocus();
        return;
    }

    // Обработка количества
    QString quantityText = quantityEdit->text().trimmed();
    if (quantityText.isEmpty()) {
        quantityText = "0";
    }

    bool quantityOk;
    int quantity = quantityText.toInt(&quantityOk);

    if (!quantityOk) {
        QMessageBox::warning(this, "Ошибка", "Некорректное количество!");
        quantityEdit->setFocus();
        return;
    }

    if (quantity < 0) {
        QMessageBox::warning(this, "Ошибка", "Количество не может быть отрицательным!");
        quantityEdit->setFocus();
        return;
    }

    // Создаем товар
    Product p(
        groupEdit->text().trimmed(),
        codeEdit->text().trimmed(),
        nameEdit->text().trimmed(),
        modelEdit->text().trimmed(),
        price,
        quantity
        );

    products.push_back(p);

    // Отладочный вывод для проверки
    qDebug() << "Добавлен товар:";
    qDebug() << "  Группа:" << p.group;
    qDebug() << "  Код:" << p.code;
    qDebug() << "  Название:" << p.name;
    qDebug() << "  Модель:" << p.model;
    qDebug() << "  Цена:" << p.price;
    qDebug() << "  Количество:" << p.quantity;

    // Очистка полей
    groupEdit->clear();
    codeEdit->clear();
    nameEdit->clear();
    modelEdit->clear();
    priceEdit->clear();
    quantityEdit->clear();

    QMessageBox::information(this, "Успех",
                             QString("Товар успешно добавлен!\nЦена: %1 руб.").arg(price, 0, 'f', 2));

    updateListDisplay();
}

void MainWindow::searchProduct()
{
    QString name = searchNameEdit->text();
    QString model = searchModelEdit->text();
    searchResult->clear();

    if (name.isEmpty() && model.isEmpty()) {
        searchResult->setPlainText("Введите хотя бы один критерий поиска");
        return;
    }

    int count = 0;
    for(const auto &p : products)
    {
        bool nameMatch = name.isEmpty() || p.name.contains(name, Qt::CaseInsensitive);
        bool modelMatch = model.isEmpty() || p.model.contains(model, Qt::CaseInsensitive);

        if(nameMatch && modelMatch)
        {
            // Выбираем эмоджи по группе - ТА ЖЕ ЛОГИКА
            QString emoji = "📦";
            QString g = p.group.toLower();

            if(g.contains("фрукт") || g.contains("яблоко") || g.contains("банан")) {
                emoji = "🍎";
            }
            else if(g.contains("овощ") || g.contains("морковь") || g.contains("картош")) {
                emoji = "🥕";
            }
            else if(g.contains("мясо") || g.contains("стейк") || g.contains("куриц")) {
                emoji = "🥩";
            }
            else if(g.contains("молочн") || g.contains("молоко") || g.contains("сыр") ||
                     g.contains("йогурт") || g == "молоко") {
                emoji = "🥛";
            }
            else if(g.contains("хлеб") || g.contains("булк") || g.contains("печень") ||
                     g.contains("торт") || g.contains("пирож")) {
                emoji = "🍞";
            }
            else if(g.contains("напит") || g.contains("вода") || g.contains("сок") ||
                     g.contains("кола")){
                emoji = "🧃";
            }

            searchResult->append(QString("%1 %2 | %3 | %4 | %5 руб. | %6 шт.")
                                     .arg(emoji)
                                     .arg(p.name)
                                     .arg(p.model)
                                     .arg(p.code)
                                     .arg(p.price, 0, 'f', 2)
                                     .arg(p.quantity));
            count++;
        }
    }

    searchResult->append(QString("\nНайдено товаров: %1").arg(count));
}

void MainWindow::updateListDisplay()
{
    listResult->clear();

    if (products.isEmpty()) {
        listResult->setPlainText("Список товаров пуст");
        statsLabel->setText("Всего товаров: 0 | Отображается: 0 | На складе: 0 шт. | Общая сумма: 0 руб.");
        return;
    }

    // Применяем фильтрацию
    QVector<Product> displayProducts = products;
    if (!filterQuantityEdit->text().isEmpty()) {
        int maxQuantity = filterQuantityEdit->text().toInt();
        displayProducts.clear();
        for(const auto& p : products) {
            if(p.quantity < maxQuantity) {
                displayProducts.push_back(p);
            }
        }
    }

    // Используем HTML для создания таблицы с data-атрибутами
    QString html = "<html><head><style>"
                   "table { border-collapse: collapse; width: 100%; }"
                   "th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }"
                   "th { background-color: #4CAF50; color: white; }"
                   "tr:nth-child(even) { background-color: #f2f2f2; }"
                   "tr:hover { background-color: #ddd; }"
                   "</style></head><body>"
                   "<table>"
                   "<tr><th>№</th><th>Эмоджи</th><th>Группа</th><th>Код</th><th>Название</th><th>Модель</th><th>Цена</th><th>Кол-во</th></tr>";

    double totalSum = 0;
    int totalItems = 0;

    for(int i = 0; i < displayProducts.size(); i++)
    {
        const Product& p = displayProducts[i];

        // Выбираем эмоджи по группе
        QString emoji = "📦";
        QString g = p.group.toLower();

        if(g.contains("фрукт") || g.contains("яблоко") || g.contains("банан")) {
            emoji = "🍎";
        } else if(g.contains("овощ") || g.contains("морковь") || g.contains("картош")) {
            emoji = "🥕";
        } else if(g.contains("мясо") || g.contains("стейк") || g.contains("куриц")) {
            emoji = "🥩";
        } else if(g.contains("молочн") || g.contains("молоко") || g.contains("сыр") || g == "молоко") {
            emoji = "🥛";
        } else if(g.contains("хлеб") || g.contains("булк") || g == "хлеб") {
            emoji = "🍞";
        } else if(g.contains("напит") || g.contains("вода") || g.contains("сок") ||
                   g.contains("кола")){
            emoji = "🧃";
        }

        // Сохраняем код товара в data-атрибуте для легкого поиска при удалении
        html += QString("<tr data-code='%1' data-name='%2' data-model='%3'>"
                        "<td>%4</td>"
                        "<td>%5</td>"
                        "<td>%6</td>"
                        "<td>%7</td>"
                        "<td>%8</td>"
                        "<td>%9</td>"
                        "<td>%10</td>"
                        "<td>%11</td>"
                        "</tr>")
                    .arg(p.code)  // data-code
                    .arg(p.name)  // data-name
                    .arg(p.model) // data-model
                    .arg(i + 1)   // №
                    .arg(emoji)   // Эмоджи
                    .arg(p.group) // Группа
                    .arg(p.code)  // Код
                    .arg(p.name)  // Название
                    .arg(p.model) // Модель
                    .arg(p.price, 0, 'f', 2) // Цена
                    .arg(p.quantity); // Количество

        totalSum += p.price * p.quantity;
        totalItems += p.quantity;
    }

    html += "</table></body></html>";

    // Добавляем итоговую информацию
    html += QString("<br><b>Итого: %1 товаров, общая стоимость: %2 руб.</b>")
                .arg(totalItems)
                .arg(totalSum, 0, 'f', 2);

    listResult->setHtml(html);

    // Обновляем статистику
    statsLabel->setText(QString("Всего товаров: %1 | Отображается: %2 | На складе: %3 шт. | Общая сумма: %4 руб.")
                            .arg(products.size())
                            .arg(displayProducts.size())
                            .arg(totalItems)
                            .arg(totalSum, 0, 'f', 2));
}


void MainWindow::saveProductsToFile()
{
    qDebug() << "СОХРАНЕНИЕ ТОВАРОВ";

    if (products.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет товаров для сохранения");
        return;
    }

    // РАБОЧИЙ СТОЛ
    QString desktopPath = QDir::homePath() + "/Desktop";
    qDebug() << "Путь:" << desktopPath;

    // СОЗДАЕМ ДИАЛОГ
    QFileDialog *dialog = new QFileDialog();
    dialog->setWindowTitle("Сохранить товары");
    dialog->setAcceptMode(QFileDialog::AcceptSave);
    dialog->setNameFilter("Text Files (*.txt)");
    dialog->setDirectory(desktopPath);
    dialog->selectFile("products.txt");

    // ВАЖНО!
    dialog->setOption(QFileDialog::DontUseNativeDialog, true); // НЕ ИСПОЛЬЗОВАТЬ НАТИВНЫЙ ДИАЛОГ!

    // ПОКАЗЫВАЕМ
    if (dialog->exec() == QDialog::Accepted) {
        QString fileName = dialog->selectedFiles().first();
        qDebug() << "Выбрано:" << fileName;

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (const auto& p : products) {
                out << p.group << "|" << p.code << "|"
                    << p.name << "|" << p.model << "|"
                    << p.price << "|" << p.quantity << "\n";
            }
            file.close();
            QMessageBox::information(this, "Успех", "Сохранено:\n" + fileName);
        }
    }

    delete dialog;
}

void MainWindow::loadProductsFromFile()
{
    qDebug() << "ЗАГРУЗКА ТОВАРОВ НАЧАТА";

    // Путь к файлу на рабочем столе
    QString fileName = QDir::homePath() + "/Desktop/products.txt";
    qDebug() << "Путь к файлу:" << fileName;

    // Проверяем, существует ли файл
    if (!QFile::exists(fileName)) {
        QMessageBox::warning(this, "Ошибка",
                             "Файл не найден на рабочем столе:\n" + fileName);
        return;
    }

    // Открываем файл
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString errorMsg = "Ошибка открытия файла: " + file.errorString();
        qDebug() << errorMsg;
        QMessageBox::critical(this, "Ошибка", errorMsg);
        return;
    }

    // Читаем файл
    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    QVector<Product> loadedProducts;
    int lineCount = 0;
    int successCount = 0;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        lineCount++;

        // Пропускаем пустые строки и заголовки
        if (line.isEmpty() || line.startsWith("===") ||
            line.startsWith("Дата") || line.startsWith("№")) {
            continue;
        }

        // Разбираем строку (формат: группа|код|название|модель|цена|количество)
        QStringList parts = line.split('|', Qt::SkipEmptyParts);

        if (parts.size() == 6) {
            bool priceOk, quantityOk;
            double price = parts[4].trimmed().toDouble(&priceOk);
            int quantity = parts[5].trimmed().toInt(&quantityOk);

            if (priceOk && quantityOk) {
                Product p(
                    parts[0].trimmed(),  // группа
                    parts[1].trimmed(),  // код
                    parts[2].trimmed(),  // название
                    parts[3].trimmed(),  // модель
                    price,
                    quantity
                    );
                loadedProducts.push_back(p);
                successCount++;
                qDebug() << "Загружен товар:" << parts[2].trimmed();
            }
        }
    }

    file.close();
    qDebug() << "Всего строк:" << lineCount << ", загружено:" << successCount;

    // Если загрузили хотя бы один товар
    if (successCount > 0) {
        products = loadedProducts;
        updateListDisplay();

        QString message = "✅ ТОВАРЫ ЗАГРУЖЕНЫ!\n\n"
                          "Файл: " + fileName + "\n"
                                       "Загружено: " + QString::number(successCount) + " товаров";

        QMessageBox::information(this, "Успех", message);
    }
    else {
        QMessageBox::warning(this, "Ошибка",
                             "Не удалось загрузить товары из файла.\n"
                             "Проверьте формат файла.\n\n"
                             "Ожидаемый формат: группа|код|название|модель|цена|количество");
    }

    qDebug() << "ЗАГРУЗКА ТОВАРОВ ЗАВЕРШЕНА";
}

void MainWindow::sortProducts()
{
    qDebug() << "СОРТИРОВКА ТОВАРОВ";

    if (products.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет товаров для сортировки");
        return;
    }

    int sortField = sortFieldCombo->currentIndex();
    qDebug() << "Выбрано поле для сортировки:" << sortField << "-" << sortFieldCombo->currentText();

    std::sort(products.begin(), products.end(), [sortField](const Product& a, const Product& b) {
        switch(sortField) {
        case 0: // Код товара - сортируем КАК ЧИСЛО
            return a.code.toInt() < b.code.toInt();

        case 1: // Наименование - как строка
            return a.name < b.name;

        case 2: // Цена - как число
            return a.price < b.price;

        case 3: // Количество - как число
            return a.quantity < b.quantity;

        default:
            return false;
        }
    });

    qDebug() << "Сортировка выполнена";
    updateListDisplay();

    QMessageBox::information(this, "Успех",
                             "Товары отсортированы по: " + sortFieldCombo->currentText());
}

void MainWindow::filterByQuantity()
{
    updateListDisplay();
}

void MainWindow::clearFilters()
{
    filterQuantityEdit->clear();
    updateListDisplay();
}

void MainWindow::showProducts()
{
    updateListDisplay();
}

// ----------------- Тестирование -----------------

void MainWindow::runBlackBoxTests()
{
    qDebug() << "=============== ЗАПУСК ТЕСТОВ ===============";

    // Формируем результаты текущего запуска
    QString currentResults;
    currentResults += "\n\n"; // Отступ перед новым запуском
    currentResults += "========================================\n";
    currentResults += "   НОВЫЙ ЗАПУСК ТЕСТОВ\n";
    currentResults += "   " + QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") + "\n";
    currentResults += "========================================\n\n";

    // ТЕСТ-КЕЙСЫ
    struct TestCase {
        QString input;
        QString description;
        bool expectedValid;
    };

    QList<TestCase> testCases = {
        {"", "Пустое поле", false},
        {"25", "Нормальный возраст (25)", true},
        {"0", "Нижняя граница (0)", true},
        {"130", "Верхняя граница (130)", true},
        {"-2", "Меньше диапазона (-2)", false},
        {"200", "Больше диапазона (200)", false},
        {" 25 ", "Пробелы вокруг числа", true},
        {"2 5", "Пробел внутри числа", false},
        {"21.5", "Точка как разделитель (21.5)", false},
        {"21,5", "Запятая как разделитель (21,5)", false},
        {"двадцать пять", "Текст вместо числа", false},
        {"abc", "Произвольный текст", false},
        {"21@#$", "Спецсимволы", false},
        {"25+", "Плюс в конце", false},
        {"001", "Ведущие нули", true},
        {"000", "Только нули", true},
        {"999999", "Очень большое число", false},
        {"   ", "Только пробелы", false},
        {"25 лет", "Число с текстом", false},
        {"возраст 25", "Текст с числом", false}
    };

    int passed = 0;
    int total = testCases.size();

    currentResults += "| № | Тест-кейс | Входные данные | Ожидаемый результат | Фактический результат | Статус |\n";
    currentResults += "|---|-----------|----------------|---------------------|----------------------|--------|\n";

    for(int i = 0; i < testCases.size(); i++) {
        const TestCase& test = testCases[i];
        QString errorMessage;
        bool result = AgeValidator::validate(test.input, errorMessage);
        bool isPass = (result == test.expectedValid);

        QString expectedStr = test.expectedValid ? "✓ Валидно" : "✗ Невалидно";
        QString actualStr = result ? "✓ Валидно" : "✗ Невалидно";
        if (!errorMessage.isEmpty()) actualStr += " (" + errorMessage + ")";

        currentResults += QString("| %1 | %2 | `%3` | %4 | %5 | %6 |\n")
                              .arg(i + 1)
                              .arg(test.description)
                              .arg(test.input)
                              .arg(expectedStr)
                              .arg(actualStr)
                              .arg(isPass ? "✅ ПРОЙДЕН" : "❌ НЕ ПРОЙДЕН");

        if (isPass) passed++;
    }

    double percentage = 100.0 * passed / total;
    currentResults += "\n## Итоги тестирования\n\n";
    currentResults += QString("- **Всего тестов:** %1\n").arg(total);
    currentResults += QString("- **Пройдено:** %1\n").arg(passed);
    currentResults += QString("- **Не пройдено:** %1\n").arg(total - passed);
    currentResults += QString("- **Успешность:** %1%\n").arg(QString::number(percentage, 'f', 1));

    currentResults += "\n## Заключение\n\n";
    currentResults += (passed == total) ? "✅ **Все тесты пройдены успешно!**\n" : "❌ **Обнаружены ошибки.**\n";
    currentResults += "\n---\n\n";

    // СОХРАНЯЕМ В ФАЙЛ
    QString fileName = QDir::homePath() + "/Desktop/black_box_test_results.md";
    QFile file(fileName);

    // Читаем старый файл
    QString oldContent;
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            oldContent = in.readAll();
            file.close();
        }
    }

    // Перезаписываем: СТАРОЕ + НОВОЕ
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out.setEncoding(QStringConverter::Utf8);

        if (!oldContent.isEmpty()) {
            out << oldContent;
            if (!oldContent.endsWith("\n\n")) out << "\n\n";
        }

        out << currentResults;
        file.close();

        qDebug() << "✅ Тесты сохранены! Размер:" << file.size() << "байт";
    }

    qDebug() << "=============== ТЕСТЫ ЗАВЕРШЕНЫ ===============";
}

// ----------------- Стиль -----------------
void MainWindow::applyStyle()
{
    setStyleSheet(
        /* Основное окно */
        "QMainWindow {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #f5f9ff, stop:1 #e3f0ff);"
        "}"

        /* Навигационные кнопки */
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "       stop:0 #5dade2, stop:1 #3498db);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 8px 16px;"
        "   font-weight: bold;"
        "   font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "       stop:0 #6eb5ff, stop:1 #4a8fe0);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "       stop:0 #2c3e50, stop:1 #34495e);"
        "}"

        /* Поля ввода - ИСПРАВЛЕНО: явно задаем цвет текста */
        "QLineEdit {"
        "   background: white;"
        "   color: #2c3e50;"                 /* Явно задаем темный цвет текста */
        "   border: 2px solid #b0c4de;"
        "   border-radius: 6px;"
        "   padding: 6px;"
        "   font-size: 13px;"
        "   selection-background-color: #5dade2;"
        "   selection-color: white;"          /* Цвет выделенного текста */
        "}"
        "QLineEdit:focus {"
        "   border-color: #3498db;"
        "   background: white;"
        "   color: #2c3e50;"
        "}"
        "QLineEdit:disabled {"
        "   background: #f0f0f0;"
        "   color: #7f8c8d;"
        "}"

        /* Плейсхолдер (текст-подсказка) */
        "QLineEdit::placeholder {"
        "   color: #95a5a6;"
        "   font-style: italic;"
        "}"

        /* Текстовые поля (QTextEdit) */
        "QTextEdit {"
        "   background: white;"
        "   color: #2c3e50;"                 /* Темный текст на белом фоне */
        "   border: 2px solid #b0c4de;"
        "   border-radius: 8px;"
        "   padding: 8px;"
        "   font-family: 'Consolas', monospace;"
        "   font-size: 12px;"
        "   selection-background-color: #5dade2;"
        "   selection-color: white;"
        "}"

        /* Комбобокс */
        "QComboBox {"
        "   background: white;"
        "   color: #2c3e50;"                 /* Темный текст */
        "   border: 2px solid #b0c4de;"
        "   border-radius: 6px;"
        "   padding: 4px;"
        "   min-width: 150px;"
        "}"
        "QComboBox:hover {"
        "   border-color: #3498db;"
        "}"
        "QComboBox::drop-down {"
        "   border: none;"
        "}"
        "QComboBox::down-arrow {"
        "   image: none;"
        "   border-left: 5px solid transparent;"
        "   border-right: 5px solid transparent;"
        "   border-top: 5px solid #3498db;"
        "   margin-right: 5px;"
        "}"

        /* Выпадающий список комбобокса */
        "QComboBox QAbstractItemView {"
        "   background: white;"
        "   color: #2c3e50;"
        "   selection-background-color: #5dade2;"
        "   selection-color: white;"
        "}"

        /* Группы */
        "QGroupBox {"
        "   background: rgba(255, 255, 255, 0.8);"
        "   color: #2c3e50;"                 /* Темный текст */
        "   border: 2px solid #b0c4de;"
        "   border-radius: 8px;"
        "   margin-top: 10px;"
        "   padding-top: 15px;"
        "   font-weight: bold;"
        "   font-size: 13px;"
        "}"

        /* Метки */
        "QLabel {"
        "   color: #2c3e50;"                 /* Темный текст */
        "   font-size: 13px;"
        "}"

        /* Статус бар */
        "QStatusBar {"
        "   background: #e3f0ff;"
        "   color: #2c3e50;"
        "}"

        /* Скроллбары */
        "QScrollBar:vertical {"
        "   background: #f0f0f0;"
        "   width: 12px;"
        "   border-radius: 6px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background: #b0c4de;"
        "   border-radius: 6px;"
        "   min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "   background: #5dade2;"
        "}"
        "QScrollBar:horizontal {"
        "   background: #f0f0f0;"
        "   height: 12px;"
        "   border-radius: 6px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "   background: #b0c4de;"
        "   border-radius: 6px;"
        "   min-width: 20px;"
        "}"
        "QScrollBar::handle:horizontal:hover {"
        "   background: #5dade2;"
        "}"

        /* Таблица */
        "QTableWidget {"
        "   background: white;"
        "   color: #2c3e50;"                 /* Темный текст */
        "   alternate-background-color: #f8fcff;"
        "   gridline-color: #d0e0f0;"
        "   border: 2px solid #b0c4de;"
        "   border-radius: 8px;"
        "}"
        "QTableWidget::item {"
        "   color: #2c3e50;"
        "   padding: 4px;"
        "}"
        "QTableWidget::item:selected {"
        "   background-color: #5dade2;"
        "   color: white;"
        "}"
        "QHeaderView::section {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "       stop:0 #e6f0fa, stop:1 #d0e4f5);"
        "   color: #2c3e50;"
        "   padding: 6px;"
        "   border: none;"
        "   font-weight: bold;"
        "}"
        );
}
