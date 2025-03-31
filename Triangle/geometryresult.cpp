#include "geometryresult.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QApplication>
#include <QFormLayout>
#include <QScreen>

GeometryResult::GeometryResult(int contentIndex, QWidget *parent)
    : QWidget(parent), stackedWidget(new QStackedWidget(this))
{
    setStyleSheet("background-color: white;");

    stackedWidget->addWidget(createTriangleWidget());
    stackedWidget->addWidget(createTetragonWidget());
    stackedWidget->addWidget(createEllipseWidget());
    stackedWidget->addWidget(createPolygonWidget());

    if(contentIndex >= 0 && contentIndex < stackedWidget->count()) {
        stackedWidget->setCurrentIndex(contentIndex);
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);

    setWindowTitle("Triangle");
    showFullScreen();
}

QWidget* GeometryResult::createTriangleWidget() {
    QWidget* widget = new QWidget();
    QHBoxLayout* mainLayout = new QHBoxLayout(widget);

    // Левая панель (ввод данных)
    QWidget* leftPanel = new QWidget();
    leftPanel->setMaximumWidth(400);
    leftPanel->setStyleSheet("QLabel { color: black; }");

    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);

    // Форма ввода координат (3 строки вместо 6)
    QFormLayout* formLayout = new QFormLayout();

    // Создаем горизонтальные компоновщики для каждой точки
    QHBoxLayout* pointALayout = new QHBoxLayout();
    QHBoxLayout* pointBLayout = new QHBoxLayout();
    QHBoxLayout* pointCLayout = new QHBoxLayout();

    // Точка A
    axEdit = new QLineEdit("-5");
    ayEdit = new QLineEdit("0");
    pointALayout->addWidget(new QLabel("Ax:"));
    pointALayout->addWidget(axEdit);
    pointALayout->addWidget(new QLabel("Ay:"));
    pointALayout->addWidget(ayEdit);
    pointALayout->addStretch();

    // Точка B
    bxEdit = new QLineEdit("0");
    byEdit = new QLineEdit("10");
    pointBLayout->addWidget(new QLabel("Bx:"));
    pointBLayout->addWidget(bxEdit);
    pointBLayout->addWidget(new QLabel("By:"));
    pointBLayout->addWidget(byEdit);
    pointBLayout->addStretch();

    // Точка C
    cxEdit = new QLineEdit("5");
    cyEdit = new QLineEdit("0");
    pointCLayout->addWidget(new QLabel("Cx:"));
    pointCLayout->addWidget(cxEdit);
    pointCLayout->addWidget(new QLabel("Cy:"));
    pointCLayout->addWidget(cyEdit);
    pointCLayout->addStretch();

    // Добавляем в форму
    formLayout->addRow( pointALayout);
    formLayout->addRow(pointBLayout);
    formLayout->addRow(pointCLayout);

    leftLayout->addLayout(formLayout);

    // Кнопка обновления
    QPushButton *updateButton = new QPushButton("Обновить треугольник");
    updateButton->setStyleSheet("background-color: white; color: black; padding: 8px;");

    // Информационная панель
    infoLabel = new QLabel();
    infoLabel->setWordWrap(true);
    QFont font;
    font.setFamily("Arial");
    infoLabel->setFont(font);
    infoLabel->setStyleSheet("color: black;");

    leftLayout->addWidget(updateButton);
    leftLayout->addWidget(infoLabel);

    // Правая панель (графика)
    triangleGraphic = new TriangleGraphic();
    triangleGraphic->setMinimumSize(600, 600);
    triangleGraphic->setFocus();

    mainLayout->addWidget(leftPanel, 1);
    mainLayout->addWidget(triangleGraphic, 2);

    connect(updateButton, &QPushButton::clicked, this, &GeometryResult::updateTriangleInfo);

    // Инициализация с дефолтными значениями
    updateTriangleInfo();

    return widget;
}

void GeometryResult::updateTriangleInfo() {
    double ax = axEdit->text().toDouble();
    double ay = ayEdit->text().toDouble();
    double bx = bxEdit->text().toDouble();
    double by = byEdit->text().toDouble();
    double cx = cxEdit->text().toDouble();
    double cy = cyEdit->text().toDouble();

    try {
        Triangle triangle(ax, ay, bx, by, cx, cy);
        triangleGraphic->setTriangleCoordinates(ax, ay, bx, by, cx, cy);

        auto sides = triangle.getSides();
        auto angles = triangle.getAngles();
        auto medians = triangle.getMedians();

        QString info = QString(
            "<b>Стороны:</b><br>"
            "AB: %1<br>BC: %2<br>AC: %3<br><br>"
            "<b>Углы:</b><br>"
            "∠A: %4°<br>∠B: %5°<br>∠C: %6°<br><br>"
            "<b>Медианы:</b><br>"
            "ma: %7<br>mb: %8<br>mc: %9"
        ).arg(sides[0], 0, 'f', 2)
         .arg(sides[1], 0, 'f', 2)
         .arg(sides[2], 0, 'f', 2)
         .arg(angles[0], 0, 'f', 2)
         .arg(angles[1], 0, 'f', 2)
         .arg(angles[2], 0, 'f', 2)
         .arg(medians[0], 0, 'f', 2)
         .arg(medians[1], 0, 'f', 2)
         .arg(medians[2], 0, 'f', 2);
         infoLabel->setStyleSheet(
               "font-family: Arial;"
               "color: black;"
               "font-size: 20px;"
               "padding: 5px;"
               "background-color: #f5f5f5;"
               "border: 1px solid #ddd;"
               "border-radius: 4px;"
           );

        infoLabel->setText(info);
    } catch (...) {
        infoLabel->setText("<span style='color:red;'>Ошибка! Невозможно построить треугольник</span>");
    }
}

void GeometryResult::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        if (isFullScreen()) {
            showNormal();

            QScreen *screen = QGuiApplication::primaryScreen();
            if (screen) {
                QRect screenGeometry = screen->availableGeometry();
                setGeometry(screenGeometry);
            }
        }
    }
    QWidget::keyPressEvent(event);
}

// Заглушки для других виджетов
QWidget* GeometryResult::createTetragonWidget() {
    QWidget *widget = new QWidget();
    widget->setLayout(new QVBoxLayout());
    widget->layout()->addWidget(new QLabel("Четырехугольник (в разработке)"));
    return widget;
}

QWidget* GeometryResult::createEllipseWidget() {
    QWidget *widget = new QWidget();
    widget->setLayout(new QVBoxLayout());
    widget->layout()->addWidget(new QLabel("Эллипс (в разработке)"));
    return widget;
}

QWidget* GeometryResult::createPolygonWidget() {
    QWidget *widget = new QWidget();
    widget->setLayout(new QVBoxLayout());
    widget->layout()->addWidget(new QLabel("Многоугольник (в разработке)"));
    return widget;
}
