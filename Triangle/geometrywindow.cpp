#include "geometrywindow.hpp"
#include "geometryresult.hpp"
#include <QLabel>
#include <QVBoxLayout>
#include <QScreen>
#include <QKeyEvent>
#include <QApplication>

GeometryWindow::GeometryWindow(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: white;");

    button1 = new QPushButton("Треугольник", this);
    button2 = new QPushButton("Четырехугольник", this);
    button3 = new QPushButton("Эллипс", this);
    button4 = new QPushButton("Многоугольник", this);

    button1->setFixedSize(800, 200);
    button2->setFixedSize(800, 200);
    button3->setFixedSize(800, 200);
    button4->setFixedSize(800, 200);
    button1->setStyleSheet("font: bold 50px Arial; color: black;");
    button2->setStyleSheet("font: bold 50px Arial; color: black;");
    button3->setStyleSheet("font: bold 50px Arial; color: black;");
    button4->setStyleSheet("font: bold 50px Arial; color: black;");

    buttonLayout = new QVBoxLayout(this);
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);
    buttonLayout->addWidget(button3);
    buttonLayout->addWidget(button4);
    buttonLayout->setAlignment(Qt::AlignCenter);

    setLayout(buttonLayout);

    connect(button1, &QPushButton::clicked, this, &GeometryWindow::openGeometryResult);
    connect(button2, &QPushButton::clicked, this, &GeometryWindow::openGeometryResult);
    connect(button3, &QPushButton::clicked, this, &GeometryWindow::openGeometryResult);
    connect(button4, &QPushButton::clicked, this, &GeometryWindow::openGeometryResult);

    setWindowTitle("Геометрические фигуры");
    showFullScreen();
}

void GeometryWindow::keyPressEvent(QKeyEvent *event) {
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

void GeometryWindow::openGeometryResult() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int index = 0;

    if (button == button1) {
        index = 0;
    }
    else if (button == button2) {
        index = 1;
    }
    else if (button == button3) {
        index = 2;
    }
    else if (button == button4) {
        index = 3;
    }

    GeometryResult *geometryResult = new GeometryResult(index);
    geometryResult->show();
    this->close();
}
