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
    void processMatrix();

private:
    int currentOperationType;

    QStackedWidget *stackedWidget;
    QGridLayout* matrixLayout;
    QGridLayout* matrixLayout2;
    QLabel* resultLabel;
    QPushButton* processButton;
    QSpinBox* rowSpin;
    QSpinBox* colSpin;
    QSpinBox* rowSpin2;
    QSpinBox* colSpin2;
    QWidget* matrix2Widget;

    QString matrixToString(Matrix& matrix) const;
    void setupMatrixSize(QGridLayout* gridLayout, int rows, int cols);
    void clearLayout(QLayout* layout);
    void setupOperationInterface();
    void updateInterface();

    QString processDeterminant(Matrix& matrix);
    QString processInverseMatrix(Matrix& matrix);
    QString processMatrixOperations(Matrix& matrix1, Matrix& matrix2);
    QString processTranspose(Matrix& matrix);
    QString processTriangleForm(Matrix& matrix);

    Matrix readMatrixFromLayout(QGridLayout* layout, int rows, int cols);
};

#endif
