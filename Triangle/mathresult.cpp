#include "mathresult.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QApplication>
#include <QScreen>
#include <QKeyEvent>
#include <QSpacerItem>

MathResult::MathResult(int operationType, QWidget *parent)
    : QWidget(parent),
      currentOperationType(operationType),
      stackedWidget(new QStackedWidget(this)),
      resultLabel(new QLabel("Введите матрицу и нажмите кнопку", this)),
      processButton(new QPushButton("Показать матрицу", this)),
      rowSpin(new QSpinBox(this)),
      colSpin(new QSpinBox(this))
{
    setStyleSheet(R"(
        QWidget {
            background-color: white;
        }
        QLabel, QSpinBox, QLineEdit, QPushButton {
            color: black;
            font-weight: bold;
            font-size: 20px;
        }
        QLineEdit {
            background-color: white;
            border: 1px solid gray;
        }
    )");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    QWidget* centerWrapper = new QWidget(this);
    QVBoxLayout* wrapperLayout = new QVBoxLayout(centerWrapper);
    wrapperLayout->setAlignment(Qt::AlignCenter);

    QHBoxLayout* controlLayout = new QHBoxLayout();
    controlLayout->setAlignment(Qt::AlignCenter);

    QLabel* rowsLabel = new QLabel("Строки:", this);
    rowsLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    controlLayout->addWidget(rowsLabel);

    rowSpin->setFixedWidth(60);
    controlLayout->addWidget(rowSpin);

    QLabel* colsLabel = new QLabel("Столбцы:", this);
    colsLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    controlLayout->addWidget(colsLabel);

    colSpin->setFixedWidth(60);
    controlLayout->addWidget(colSpin);

    controlLayout->insertStretch(0, 1);
    controlLayout->addStretch(1);

    matrixLayout = new QGridLayout();
    matrixLayout->setAlignment(Qt::AlignCenter);

    rowSpin->setRange(1, 10);
    colSpin->setRange(1, 10);
    rowSpin->setValue(3);
    colSpin->setValue(3);

    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setMinimumWidth(400);

    wrapperLayout->addLayout(controlLayout);
    wrapperLayout->addLayout(matrixLayout);
    wrapperLayout->addWidget(processButton, 0, Qt::AlignCenter);
    wrapperLayout->addWidget(resultLabel);

    mainLayout->addWidget(centerWrapper);

    connect(rowSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MathResult::updateMatrixSize);
    connect(colSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MathResult::updateMatrixSize);
    connect(processButton, &QPushButton::clicked,
            this, &MathResult::processMatrix);

    setupOperationInterface();
    updateMatrixSize();
    showFullScreen();
}

void MathResult::setupOperationInterface() {
    switch (currentOperationType) {
    case 0: // Определитель
        processButton->setText("Вычислить определитель");
        break;
    case 1: // Обратная матрица
        processButton->setText("Найти обратную матрицу");
        colSpin->setValue(rowSpin->value()); // Для квадратной матрицы
        break;
    case 2: // Операции
        processButton->setText("Выполнить операции");
        break;
    case 3: // Транспонирование
        processButton->setText("Транспонировать");
        break;
    case 4: // Треугольный вид
        processButton->setText("Привести к треугольному виду");
        break;
    }
}

QString MathResult::matrixToString(Matrix& matrix) const {
    QString result;
    int rows = matrix.getRows();
    int cols = matrix.getCols();

    result += "Матрица " + QString::number(rows) + "x" + QString::number(cols) + ":\n";
    result += "                                          \n";

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            Fraction frac = matrix(r, c);
            if (frac.getDown() == 1) {
                result += QString::number(frac.getUp());
            } else {
                if (frac.getUp() < 0 || frac.getDown() < 0) {
                    result += "-" + QString::number(abs(frac.getUp())) + "/" + QString::number(abs(frac.getDown()));
                } else {
                    result += QString::number(frac.getUp()) + "/" + QString::number(frac.getDown());
                }
            }
            result += "\t";
        }
        result += "\n";
    }
    return result;
}

void MathResult::setupMatrixSize() {
    clearLayout();
    int rows = rowSpin->value();
    int cols = colSpin->value();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            QLineEdit* edit = new QLineEdit(this);
            edit->setAlignment(Qt::AlignCenter);
            edit->setText("0");
            edit->setMaximumWidth(60);
            matrixLayout->addWidget(edit, r, c);
        }
    }
}

void MathResult::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        if (isFullScreen()) {
            showNormal();

            QScreen *screen = QGuiApplication::primaryScreen();
            if (screen) {
                QRect screenGeometry = screen->availableGeometry();
                setGeometry(screenGeometry);
            }
        }
    }
    QWidget::keyPressEvent(event);
}

void MathResult::updateMatrixSize() {
    setupMatrixSize();
}

void MathResult::processMatrix() {
    int rows = rowSpin->value();
    int cols = colSpin->value();

    Matrix matrix(rows, cols);

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            QLayoutItem* item = matrixLayout->itemAtPosition(r, c);
            if (!item || !item->widget()) continue;

            QLineEdit* edit = qobject_cast<QLineEdit*>(item->widget());
            if (!edit) continue;

            QString text = edit->text();
            if (text.contains('/')) {
                QStringList parts = text.split('/');
                if (parts.size() == 2) {
                    matrix(r, c) = Fraction(parts[0].toInt(), parts[1].toInt());
                }
            } else {
                matrix(r, c) = Fraction(text.toInt(), 1);
            }
        }
    }

    QString resultText;

    switch (currentOperationType) {
    case 0: // Определитель
        resultText = processDeterminant(matrix);
        break;
    case 1: // Обратная матрица
        resultText = processInverseMatrix(matrix);
        break;
    case 2: // Операции
        resultText = processMatrixOperations(matrix);
        break;
    case 3: // Транспонирование
        resultText = processTranspose(matrix);
        break;
    case 4: // Треугольный вид
        resultText = processTriangleForm(matrix);
        break;
    }

    resultLabel->setText(resultText);
    resultLabel->setAlignment(Qt::AlignCenter);
}

QString MathResult::processDeterminant(Matrix& matrix) {
    if (matrix.getRows() != matrix.getCols()) {
        return "Ошибка: матрица должна быть квадратной для вычисления определителя!";
    }

    try {
        Fraction det = matrix.determinant();
        QString result = "Матрица:\n" + matrixToString(matrix);
        result += "\nОпределитель: ";
        if (det.getDown() == 1) {
            result += QString::number(det.getUp());
        } else {
            result += QString::number(det.getUp()) + "/" + QString::number(det.getDown());
        }
        return result;
    } catch (...) {
        return "Ошибка при вычислении определителя!";
    }
}

QString MathResult::processInverseMatrix(Matrix& matrix) {
    if (matrix.getRows() != matrix.getCols()) {
        return "Ошибка: матрица должна быть квадратной!";
    }

    try {
        Matrix* inverse = matrix.inverseMatrix();
        if (inverse) {
            QString result = "Исходная матрица:\n" + matrixToString(matrix);
            result += "\n\nОбратная матрица:\n" + matrixToString(*inverse);
            delete inverse;
            return result;
        }
        return "Обратной матрицы не существует!";
    } catch (...) {
        return "Ошибка при вычислении обратной матрицы!";
    }
}

QString MathResult::processTranspose(Matrix& matrix) {
    Matrix transposed = matrix.transpose();
    QString result = "Исходная матрица:\n" + matrixToString(matrix);
    result += "\n\nТранспонированная матрица:\n" + matrixToString(transposed);
    return result;
}

QString MathResult::processTriangleForm(Matrix& matrix) {
    Matrix* triangle = matrix.triangleMatrix();
    QString result = "Исходная матрица:\n" + matrixToString(matrix);
    result += "\n\nТреугольная форма:\n" + matrixToString(*triangle);
    delete triangle;
    return result;
}

QString MathResult::processMatrixOperations(Matrix& matrix) {
    return "Операции с матрицами (в разработке):\n" + matrixToString(matrix);
}

void MathResult::clearLayout() {
    QLayoutItem* item;
    while ((item = matrixLayout->takeAt(0))) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}
