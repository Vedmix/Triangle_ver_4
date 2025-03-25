#ifndef MATHWINDOW_H
#define MATHWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MathWindow : public QWidget {
    Q_OBJECT
public:
    explicit MathWindow(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void openSecondMathMenu();

private:
    QPushButton *button1;
    QPushButton *button2;
    QVBoxLayout *buttonLayout;
};

#endif
