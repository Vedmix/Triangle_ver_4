#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include <QScreen>

class WelcomeWindow : public QWidget {
public:
    WelcomeWindow(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif
