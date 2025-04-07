#ifndef GEOMETRYRESULT_H
#define GEOMETRYRESULT_H

#include <QWidget>
#include <QStackedWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QScreen>
#include <QSpinBox>
#include "math/matrix.h"

class MathResult : public QWidget
{
    Q_OBJECT

public:
    explicit MathResult(int contentIndex = 0, QWidget *parent = nullptr);
    ~MathResult() = default;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateMatrixSize();
    void processMatrix();

private:
    QStackedWidget *stackedWidget;

    QWidget* createDeterminatorRank();
    QWidget* createTranspose();
    QWidget* createInverseMatrix();
    QWidget* createMatrixOperations();
    QString matrixToString(Matrix& matrix) const;

    QGridLayout* matrixLayout;
    QLabel* resultLabel;
    QPushButton* processButton;
    QSpinBox* rowSpin;
    QSpinBox* colSpin;

    void clearLayout();
};

#endif
