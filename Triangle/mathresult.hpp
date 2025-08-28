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
#include "math/matrix.hpp"

class MathResult : public QWidget
{
    Q_OBJECT

public:
    explicit MathResult(int operationType = 0, QWidget *parent = nullptr);
    ~MathResult() = default;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateMatrixSize();
    void processMatrix();

private:
    int currentOperationType;
    QStackedWidget *stackedWidget;
    QGridLayout* matrixLayout;
    QLabel* resultLabel;
    QPushButton* processButton;
    QSpinBox* rowSpin;
    QSpinBox* colSpin;

    QString matrixToString(Matrix& matrix) const;
    void setupMatrixSize();
    void clearLayout();
    void setupOperationInterface();

    QString processDeterminant(Matrix& matrix);
    QString processInverseMatrix(Matrix& matrix);
    QString processMatrixOperations(Matrix& matrix);
    QString processTranspose(Matrix& matrix);
    QString processTriangleForm(Matrix& matrix);
};

#endif
