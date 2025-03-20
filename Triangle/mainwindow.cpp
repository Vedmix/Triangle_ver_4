#include "mainwindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>

MyWindow::MyWindow(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: white;");

    QPushButton *button1 = new QPushButton("Кнопка 1", this);
    QPushButton *button2 = new QPushButton("Кнопка 2", this);

    button1->setFixedSize(100, 50);
    button2->setFixedSize(100, 50);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(button1);
    layout->addWidget(button2);

    setLayout(layout);

    setWindowTitle("Triangle");

    showFullScreen();
}

void MyWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        if (isFullScreen()) {
            showNormal();

            QScreen *screen = QGuiApplication::primaryScreen();
            QRect screenGeometry = screen->availableGeometry();

            setGeometry(screenGeometry);
        }
    }
}
