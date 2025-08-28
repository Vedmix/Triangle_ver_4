#include "secmathwindow.hpp"
#include "mathresult.hpp"
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

    matrixButton1 = new QPushButton("Нахождение определителя", widget);
    matrixButton2 = new QPushButton("Нахождение обратной матрицы", widget);
    matrixButton3 = new QPushButton("Математические операции", widget);
    matrixButton4 = new QPushButton("Транспонирование матрицы", widget);
    matrixButton5 = new QPushButton("Приведение к треугольному виду", widget);

    matrixButton1->setStyleSheet("font: bold 50px Arial; color: black;");
    matrixButton2->setStyleSheet("font: bold 50px Arial; color: black;");
    matrixButton3->setStyleSheet("font: bold 50px Arial; color: black;");
    matrixButton4->setStyleSheet("font: bold 50px Arial; color: black;");
    matrixButton5->setStyleSheet("font: bold 50px Arial; color: black;");

    matrixButton1->setFixedSize(900, 100);
    matrixButton2->setFixedSize(900, 100);
    matrixButton3->setFixedSize(900, 100);
    matrixButton4->setFixedSize(900, 100);
    matrixButton5->setFixedSize(900, 100);

    connect(matrixButton1, &QPushButton::clicked, this, &SecondMathMenu::openMathResult);
    connect(matrixButton2, &QPushButton::clicked, this, &SecondMathMenu::openMathResult);
    connect(matrixButton3, &QPushButton::clicked, this, &SecondMathMenu::openMathResult);
    connect(matrixButton4, &QPushButton::clicked, this, &SecondMathMenu::openMathResult);
    connect(matrixButton5, &QPushButton::clicked, this, &SecondMathMenu::openMathResult);

    layout->addWidget(matrixButton1);
    layout->addWidget(matrixButton2);
    layout->addWidget(matrixButton3);
    layout->addWidget(matrixButton4);
    layout->addWidget(matrixButton5);
    layout->setAlignment(Qt::AlignCenter);

    widget->setLayout(layout);
    return widget;
}

void SecondMathMenu::openMathResult() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int operationType = -1;

    if (button == matrixButton1) {
        operationType = 0; // Определитель
    } else if (button == matrixButton2) {
        operationType = 1; // Обратная матрица
    } else if (button == matrixButton3) {
        operationType = 2; // Математические операции
    } else if (button == matrixButton4) {
        operationType = 3; // Транспонирование
    } else if (button == matrixButton5) {
        operationType = 4; // Треугольный вид
    }

    if (operationType != -1) {
        emit matrixOperationSelected(operationType);
    }

    MathResult *mathResult = new MathResult(operationType);
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
