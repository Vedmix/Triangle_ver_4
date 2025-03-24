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

    // Добавьте слоты для обработки нажатий кнопок
    void handleMatrixButton1();
    void handleMatrixButton2();
    void handleMatrixButton3();
    void handleMatrixButton4();
    void handleMatrixButton5();

private:
    QStackedWidget *stackedWidget;

    QWidget *createMatrixWidget();
    QWidget *createComplexNumbersWidget();

    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QPushButton *button5;
    QVBoxLayout *buttonLayout;
};

#endif
