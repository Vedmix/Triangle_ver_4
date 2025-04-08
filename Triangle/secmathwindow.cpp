#include "secmathwindow.h"
#include "mathresult.h"
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

    matrixButton1 = new QPushButton("Определитель / Ранг", widget);
    matrixButton2 = new QPushButton("Транспонирование", widget);
    matrixButton3 = new QPushButton("Обратная матрица", widget);
    matrixButton4 = new QPushButton("Действия (*, +, -, *k)", widget);

    matrixButton1->setStyleSheet("font: bold 50px Arial; color: black;");
    matrixButton2->setStyleSheet("font: bold 50px Arial; color: black;");
    matrixButton3->setStyleSheet("font: bold 50px Arial; color: black;");
    matrixButton4->setStyleSheet("font: bold 50px Arial; color: black;");

    matrixButton1->setFixedSize(800, 100);
    matrixButton2->setFixedSize(800, 100);
    matrixButton3->setFixedSize(800, 100);
    matrixButton4->setFixedSize(800, 100);

    connect(matrixButton1, &QPushButton::clicked, this, &SecondMathMenu::openMathResult);
    connect(matrixButton2, &QPushButton::clicked, this, &SecondMathMenu::openMathResult);
    connect(matrixButton3, &QPushButton::clicked, this, &SecondMathMenu::openMathResult);
    connect(matrixButton4, &QPushButton::clicked, this, &SecondMathMenu::openMathResult);

    layout->addWidget(matrixButton1);
    layout->addWidget(matrixButton2);
    layout->addWidget(matrixButton3);
    layout->addWidget(matrixButton4);
    layout->setAlignment(Qt::AlignCenter);

    widget->setLayout(layout);
    return widget;
}

void SecondMathMenu::openMathResult() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int index = 0;
    if (button == matrixButton1) {
        index = 0; // Определитель / Ранг
    } else if (button == matrixButton2) {
        index = 1; // Транспонирование
    } else if (button == matrixButton3) {
        index = 2; // Обратная матрица
    } else if (button == matrixButton4) {
        index = 3; // Действия с матрицами
    }

    MathResult *mathResult = new MathResult(index);
    mathResult->show();
    this->close();
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
