#ifndef MATHWINDOW_H
#define MATHWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class MathWindow : public QWidget {
    Q_OBJECT
protected:
    void keyPressEvent(QKeyEvent *event);
public:
    explicit MathWindow(QWidget *parent = nullptr);
};

#endif // MATHWINDOW_H
