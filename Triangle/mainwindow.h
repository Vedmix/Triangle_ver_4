#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class WelcomeWindow : public QWidget {
    Q_OBJECT
public:
    explicit WelcomeWindow(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void openMathWindow();
    void openGeometryWindow();


private:
    QPushButton *button1;
    QPushButton *button2;
};

#endif
