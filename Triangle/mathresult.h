#ifndef GEOMETRYRESULT_H
#define GEOMETRYRESULT_H

#include <QWidget>
#include <QStackedWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>

class MathResult : public QWidget
{
    Q_OBJECT

public:
    explicit MathResult(int contentIndex = 0, QWidget *parent = nullptr);
    ~MathResult() = default;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QStackedWidget *stackedWidget;

    QWidget* createDeterminatorRank();
    QWidget* createTranspose();
    QWidget* createInverseMatrix();
    QWidget* createMatrixOperations();
};

#endif
