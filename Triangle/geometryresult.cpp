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

    QWidget* leftPanel = new QWidget();
    leftPanel->setMaximumWidth(400);
    leftPanel->setStyleSheet("QLabel { color: black; }");

    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);

    QFormLayout* formLayout = new QFormLayout();

    QHBoxLayout* pointALayout = new QHBoxLayout();
    QHBoxLayout* pointBLayout = new QHBoxLayout();
    QHBoxLayout* pointCLayout = new QHBoxLayout();

    axEdit = new QLineEdit("-5");
    ayEdit = new QLineEdit("0");
    pointALayout->addWidget(new QLabel("Ax:"));
    pointALayout->addWidget(axEdit);
    pointALayout->addWidget(new QLabel("Ay:"));
    pointALayout->addWidget(ayEdit);
    pointALayout->addStretch();

    bxEdit = new QLineEdit("0");
    byEdit = new QLineEdit("10");
    pointBLayout->addWidget(new QLabel("Bx:"));
    pointBLayout->addWidget(bxEdit);
    pointBLayout->addWidget(new QLabel("By:"));
    pointBLayout->addWidget(byEdit);
    pointBLayout->addStretch();

    cxEdit = new QLineEdit("5");
    cyEdit = new QLineEdit("0");
    pointCLayout->addWidget(new QLabel("Cx:"));
    pointCLayout->addWidget(cxEdit);
    pointCLayout->addWidget(new QLabel("Cy:"));
    pointCLayout->addWidget(cyEdit);
    pointCLayout->addStretch();

    formLayout->addRow( pointALayout);
    formLayout->addRow(pointBLayout);
    formLayout->addRow(pointCLayout);

    leftLayout->addLayout(formLayout);

    QPushButton *updateButton = new QPushButton("Обновить координаты");
    updateButton->setStyleSheet("background-color: white; color: black; padding: 8px;");

    infoLabel = new QLabel();
    infoLabel->setWordWrap(true);
    QFont font;
    font.setFamily("Arial");
    infoLabel->setFont(font);
    infoLabel->setStyleSheet("color: black;");

    leftLayout->addWidget(updateButton);
    leftLayout->addWidget(infoLabel);

    triangleGraphic = new TriangleGraphic();
    triangleGraphic->setMinimumSize(600, 600);
    triangleGraphic->setFocus();

    mainLayout->addWidget(leftPanel, 1);
    mainLayout->addWidget(triangleGraphic, 2);

    connect(updateButton, &QPushButton::clicked, this, &GeometryResult::updateTriangleInfo);

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
        auto type = triangle.getType();
        auto square = triangle.getSquare();

        QString info = QString(
            "<b>Тип:</b><br>"
            "%1<br><br>"
            "<b>Периметр:</b><br>"
            "P = %2<br><br>"
            "<b>Площадь:</b><br>"
            "S = %3<br><br>"
            "<b>Стороны:</b><br>"
            "AB: %4<br>BC: %5<br>AC: %6<br><br>"
            "<b>Углы:</b><br>"
            "∠A: %7°<br>∠B: %8°<br>∠C: %9°<br><br>"
            "<b>Медианы:</b><br>"
            "AA1: %10<br>BB1: %11<br>CC1: %12"
         ).arg(QString::fromStdString(type[0]))
         .arg(square[1], 0, 'f', 3)
         .arg(square[0], 0, 'f', 3)
         .arg(sides[0], 0, 'f', 3)
         .arg(sides[1], 0, 'f', 3)
         .arg(sides[2], 0, 'f', 3)
         .arg(angles[0], 0, 'f', 3)
         .arg(angles[1], 0, 'f', 3)
         .arg(angles[2], 0, 'f', 3)
         .arg(medians[0], 0, 'f', 3)
         .arg(medians[1], 0, 'f', 3)
         .arg(medians[2], 0, 'f', 3);

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
