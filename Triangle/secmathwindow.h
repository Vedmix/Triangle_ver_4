#ifndef SECONDMATHMENU_H
#define SECONDMATHMENU_H

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>

class SecondMathMenu : public QWidget {
    Q_OBJECT
public:
    explicit SecondMathMenu(int contentIndex = 0, QWidget *parent = nullptr);

private slots:
    void showMatrixContent();
    void showComplexNumbersContent();
    void keyPressEvent(QKeyEvent *event);
    void openMathResult();

private:
    QStackedWidget *stackedWidget;
    QPushButton *matrixButton1;
    QPushButton *matrixButton2;
    QPushButton *matrixButton3;
    QPushButton *matrixButton4;

    QWidget *createMatrixWidget();
    QWidget *createComplexNumbersWidget();
};

#endif
