#include "geometryresult.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QKeyEvent>
#include <QApplication>

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
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    QLabel *label = new QLabel("Triangle", this);
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(100);

    label->setFont(font);
    label->setStyleSheet("color: red;");
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(label);
    mainLayout->setAlignment(Qt::AlignCenter);
    return widget;
}

QWidget* GeometryResult::createTetragonWidget() {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(new QLabel("Tetragon Content", widget));

    return widget;
}

QWidget* GeometryResult::createEllipseWidget() {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(new QLabel("Ellipse Content", widget));

    return widget;
}

QWidget* GeometryResult::createPolygonWidget() {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(new QLabel("Polygon Content", widget));

    return widget;
}

void GeometryResult::showTriangleContent() { stackedWidget->setCurrentIndex(0); }
void GeometryResult::showTetragonContent() { stackedWidget->setCurrentIndex(1); }
void GeometryResult::showEllipseContent() { stackedWidget->setCurrentIndex(2); }
void GeometryResult::showPolygonContent() { stackedWidget->setCurrentIndex(3); }

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
