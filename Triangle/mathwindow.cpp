#include "mathwindow.h"
#include "secmathwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QScreen>
#include <QKeyEvent>
#include <QApplication>

MathWindow::MathWindow(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: white;");

    setWindowTitle("Triangle");

    button1 = new QPushButton("Матрицы", this);
    button2 = new QPushButton("Комплексные числа", this);

    button1->setFixedSize(800, 200);
    button2->setFixedSize(800, 200);

    button1->setStyleSheet("font: bold 50px Arial; color: black;");
    button2->setStyleSheet("font: bold 50px Arial; color: black;");

    buttonLayout = new QVBoxLayout(this);
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);

    buttonLayout->setAlignment(Qt::AlignCenter);

    connect(button1, &QPushButton::clicked, this, &MathWindow::openSecondMathMenu);
    connect(button2, &QPushButton::clicked, this, &MathWindow::openSecondMathMenu);

    showFullScreen();
}

void MathWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        if (isFullScreen()) {
            showNormal();

            QScreen *screen = QGuiApplication::primaryScreen();
            QRect screenGeometry = screen->availableGeometry();

            setGeometry(screenGeometry);
        }
    }
}

void MathWindow::openSecondMathMenu() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int index = 0;

    if (button == button2) {
        index = 1;
    }

    SecondMathMenu *secondMathMenu = new SecondMathMenu(index);
    secondMathMenu->show();
    this->close();
}
