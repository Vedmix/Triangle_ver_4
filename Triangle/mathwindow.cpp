#include "mathwindow.h"
#include <QLabel>
#include <QLabel>
#include <QVBoxLayout>
#include <QScreen>
#include <QKeyEvent>
#include <QApplication>

MathWindow::MathWindow(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: white;");

    setWindowTitle("Triangle");

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
