#include <QApplication>
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    WelcomeWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
