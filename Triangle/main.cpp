#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    WelcomeWindow window;
    window.show();

    return app.exec();
}
