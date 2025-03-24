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
    void openSecondMathMenu();  // Объявляем метод для открытия SecondMathMenu

private:
    QPushButton *button1;  // Кнопка "Матрицы"
    QPushButton *button2;  // Кнопка "Комплексные числа"
    QVBoxLayout *buttonLayout;  // Layout для кнопок
};

#endif // MATHWINDOW_H
