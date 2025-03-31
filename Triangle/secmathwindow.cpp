#include "secmathwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QKeyEvent>
#include <QApplication>

SecondMathMenu::SecondMathMenu(int contentIndex, QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: white;");

    stackedWidget = new QStackedWidget(this);

    stackedWidget->addWidget(createMatrixWidget());
    stackedWidget->addWidget(createComplexNumbersWidget());

    stackedWidget->setCurrentIndex(contentIndex);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);

    setLayout(mainLayout);

    setWindowTitle("Second Math Menu");
    showFullScreen();
}



QWidget* SecondMathMenu::createMatrixWidget() {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QPushButton *matrixButton1 = new QPushButton("Определитель", widget);
    QPushButton *matrixButton2 = new QPushButton("Ранг", widget);
    QPushButton *matrixButton3 = new QPushButton("Транспонирование", widget);
    QPushButton *matrixButton4 = new QPushButton("Обратная матрица", widget);
    QPushButton *matrixButton5 = new QPushButton("Действия (*, +, -, *k)", widget);

    matrixButton1->setStyleSheet("font: bold 50px Arial; color: black;");
    matrixButton2->setStyleSheet("font: bold 50px Arial; color: black;");
    matrixButton3->setStyleSheet("font: bold 50px Arial; color: black;");
    matrixButton4->setStyleSheet("font: bold 50px Arial; color: black;");
    matrixButton5->setStyleSheet("font: bold 50px Arial; color: black;");

    matrixButton1->setFixedSize(800, 100);
    matrixButton2->setFixedSize(800, 100);
    matrixButton3->setFixedSize(800, 100);
    matrixButton4->setFixedSize(800, 100);
    matrixButton5->setFixedSize(800, 100);

    connect(matrixButton1, &QPushButton::clicked, this, &SecondMathMenu::handleMatrixButton1);
    connect(matrixButton2, &QPushButton::clicked, this, &SecondMathMenu::handleMatrixButton2);
    connect(matrixButton3, &QPushButton::clicked, this, &SecondMathMenu::handleMatrixButton3);
    connect(matrixButton4, &QPushButton::clicked, this, &SecondMathMenu::handleMatrixButton4);
    connect(matrixButton5, &QPushButton::clicked, this, &SecondMathMenu::handleMatrixButton5);

    layout->addWidget(matrixButton1);
    layout->addWidget(matrixButton2);
    layout->addWidget(matrixButton3);
    layout->addWidget(matrixButton4);
    layout->addWidget(matrixButton5);
    layout->setAlignment(Qt::AlignCenter);

    widget->setLayout(layout);

    return widget;
}
void SecondMathMenu::handleMatrixButton1() {
    // Обработка нажатия кнопки "Определитель"
    qDebug() << "Определитель нажат";
}

void SecondMathMenu::handleMatrixButton2() {
    // Обработка нажатия кнопки "Ранг"
    qDebug() << "Ранг нажат";
}

void SecondMathMenu::handleMatrixButton3() {
    // Обработка нажатия кнопки "Транспонирование"
    qDebug() << "Транспонирование нажат";
}

void SecondMathMenu::handleMatrixButton4() {
    // Обработка нажатия кнопки "Обратная матрица"
    qDebug() << "Обратная матрица нажата";
}

void SecondMathMenu::handleMatrixButton5() {
    // Обработка нажатия кнопки "Действия (*, +, -, *k)"
    qDebug() << "Действия с матрицами нажаты";
}

QWidget* SecondMathMenu::createComplexNumbersWidget() {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QPushButton *complexButton1 = new QPushButton("Комплексное число 1", widget);
    QPushButton *complexButton2 = new QPushButton("Комплексное число 2", widget);

    complexButton1->setStyleSheet("font: bold 30px Arial; color: black;");
    complexButton2->setStyleSheet("font: bold 30px Arial; color: black;");

    layout->addWidget(complexButton1);
    layout->addWidget(complexButton2);

    widget->setLayout(layout);

    return widget;
}

void SecondMathMenu::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        if (isFullScreen()) {
            showNormal();

            QScreen *screen = QGuiApplication::primaryScreen();
            QRect screenGeometry = screen->availableGeometry();

            setGeometry(screenGeometry);
        }
    }
}

void SecondMathMenu::showMatrixContent() {
    stackedWidget->setCurrentIndex(0);
}

void SecondMathMenu::showComplexNumbersContent() {
    stackedWidget->setCurrentIndex(1);
}
