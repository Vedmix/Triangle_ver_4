#include "mainwindow.h"
#include "mathwindow.h"
#include "geometrywindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QScreen>
#include <QKeyEvent>


WelcomeWindow::WelcomeWindow(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: white;");

    button1 = new QPushButton("Математика", this);
    button2 = new QPushButton("Геометрия", this);
    QLabel *label = new QLabel("Triangle", this);

    button1->setFixedSize(800, 200);
    button2->setFixedSize(800, 200);
    button1->setStyleSheet("font: bold 50px Arial; color: black;");
    button2->setStyleSheet("font: bold 50px Arial; color: black;");

    QFont font;
    font.setFamily("Arial");
    font.setPointSize(100);

    label->setFont(font);
    label->setStyleSheet("color: red;");
    label->setAlignment(Qt::AlignCenter);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);
    buttonLayout->setAlignment(Qt::AlignCenter);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(label);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setSpacing(200);
    mainLayout->setAlignment(Qt::AlignCenter);

    setLayout(mainLayout);

    setWindowTitle("Triangle");


    connect(button1, &QPushButton::clicked, this, &WelcomeWindow::openMathWindow);
    connect(button2, &QPushButton::clicked, this, &WelcomeWindow::openGeometryWindow);

    showFullScreen();
}

void WelcomeWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        if (isFullScreen()) {
            showNormal();

            QScreen *screen = QGuiApplication::primaryScreen();
            QRect screenGeometry = screen->availableGeometry();

            setGeometry(screenGeometry);
        }
    }
}

void WelcomeWindow::openMathWindow() {
    MathWindow *mathWindow = new MathWindow();
    mathWindow->show();
    this->close();
}

void WelcomeWindow::openGeometryWindow() {
    GeometryWindow *geometryWindow = new GeometryWindow();
    geometryWindow->show();
    this->close();
}
