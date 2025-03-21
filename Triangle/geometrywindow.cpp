#include "geometrywindow.h"
#include <QLabel>
#include <QLabel>
#include <QVBoxLayout>
#include <QScreen>
#include <QKeyEvent>
#include <QApplication>

GeometryWindow::GeometryWindow(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: white;");

    setWindowTitle("Triangle");

    showFullScreen();
}

void GeometryWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        if (isFullScreen()) {
            showNormal();

            QScreen *screen = QGuiApplication::primaryScreen();
            QRect screenGeometry = screen->availableGeometry();

            setGeometry(screenGeometry);
        }
    }
}
