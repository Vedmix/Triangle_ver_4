#include "mathresult.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QApplication>
#include <QScreen>

MathResult::MathResult(int contentIndex, QWidget *parent)
    : QWidget(parent), stackedWidget(new QStackedWidget(this))
{
    setStyleSheet("background-color: white;");

    stackedWidget->addWidget(createDeterminatorRank());
    stackedWidget->addWidget(createTranspose());
    stackedWidget->addWidget(createInverseMatrix());
    stackedWidget->addWidget(createMatrixOperations());

    if (contentIndex >= 0 && contentIndex < stackedWidget->count()) {
        stackedWidget->setCurrentIndex(contentIndex);
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);

    setWindowTitle("Matrix Operations");
    showFullScreen();
}

QWidget* MathResult::createDeterminatorRank() {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(new QLabel("Определитель / Ранг матрицы (в разработке)"));
    return widget;
}

QWidget* MathResult::createTranspose() {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(new QLabel("Транспонирование матрицы (в разработке)"));
    return widget;
}

QWidget* MathResult::createInverseMatrix() {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(new QLabel("Обратная матрица (в разработке)"));
    return widget;
}

QWidget* MathResult::createMatrixOperations() {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(new QLabel("Действия с матрицами (*, +, -, *k) (в разработке)"));
    return widget;
}

void MathResult::keyPressEvent(QKeyEvent *event) {
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
