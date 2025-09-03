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
      colSpin(new QSpinBox(this)),
      rowSpin2(new QSpinBox(this)),
      colSpin2(new QSpinBox(this)),
      matrix2Widget(new QWidget(this))
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

    //основной Layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    QWidget* centerWrapper = new QWidget(this);
    QVBoxLayout* wrapperLayout = new QVBoxLayout(centerWrapper);
    wrapperLayout->setAlignment(Qt::AlignCenter);
    
    //контроль первой матрицы
    QHBoxLayout* controlLayout = new QHBoxLayout();
    controlLayout->setAlignment(Qt::AlignCenter);

    QLabel* rowsLabel = new QLabel("Строки A:", this);
    QLabel* colsLabel = new QLabel("Столбцы A:", this);
    
    controlLayout->addWidget(rowsLabel);
    controlLayout->addWidget(rowSpin);
    controlLayout->addWidget(colsLabel);
    controlLayout->addWidget(colSpin);
    
    //общий Layout
    QHBoxLayout* matricesLayout = new QHBoxLayout();
    matricesLayout->setAlignment(Qt::AlignCenter);
    
    //первая матрица 
    QWidget* matrix1Widget = new QWidget();
    QVBoxLayout* matrix1Layout = new QVBoxLayout(matrix1Widget);
    matrix1Layout->addLayout(controlLayout);
    
    matrixLayout = new QGridLayout();
    matrixLayout->setSpacing(15);
    matrixLayout->setHorizontalSpacing(20);
    matrixLayout->setVerticalSpacing(15);
    matrixLayout->setAlignment(Qt::AlignCenter);

    matrix1Layout->addLayout(matrixLayout);
    matricesLayout->addWidget(matrix1Widget);

    //вторая матрица
    QVBoxLayout* matrix2MainLayout = new QVBoxLayout(matrix2Widget);

    QHBoxLayout* controlLayout2 = new QHBoxLayout();
    controlLayout2->setAlignment(Qt::AlignCenter);

    QLabel* rowsLabel2 = new QLabel("Строки B:", this);
    QLabel* colsLabel2 = new QLabel("Столбцы B:", this);
    
    controlLayout2->addWidget(rowsLabel2);
    controlLayout2->addWidget(rowSpin2);
    controlLayout2->addWidget(colsLabel2);
    controlLayout2->addWidget(colSpin2);
    
    matrixLayout2 = new QGridLayout();
    matrixLayout2->setSpacing(15);
    matrixLayout2->setHorizontalSpacing(20);
    matrixLayout2->setVerticalSpacing(15);
    matrixLayout2->setAlignment(Qt::AlignCenter);

    matrix2MainLayout->addLayout(controlLayout2);
    matrix2MainLayout->addLayout(matrixLayout2);
    
    matricesLayout->addWidget(matrix2Widget);
    
    //настройка спинов
    rowSpin->setRange(1, 10);
    colSpin->setRange(1, 10);
    rowSpin->setValue(2);
    colSpin->setValue(2);
    
    rowSpin2->setRange(1, 10);
    colSpin2->setRange(1, 10);
    rowSpin2->setValue(2);
    colSpin2->setValue(2);
    
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setMinimumWidth(600);
    
    wrapperLayout->addLayout(matricesLayout);
    wrapperLayout->addWidget(processButton, 0, Qt::AlignCenter);
    wrapperLayout->addWidget(resultLabel);
    
    mainLayout->addWidget(centerWrapper);
    
    setupMatrixSize(matrixLayout, rowSpin->value(), colSpin->value());
    setupMatrixSize(matrixLayout2, rowSpin2->value(), colSpin2->value());

    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setMinimumWidth(600);
    
    // подключение сигналов
    connect(rowSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this,[this]() {setupMatrixSize(matrixLayout,
                           rowSpin->value(), colSpin->value());});
    connect(colSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this,[this]() {setupMatrixSize(matrixLayout,
                           rowSpin->value(), colSpin->value());});
    connect(rowSpin2, QOverload<int>::of(&QSpinBox::valueChanged),
            this,[this]() {setupMatrixSize(matrixLayout2,
                           rowSpin2->value(), colSpin2->value());});
    connect(colSpin2, QOverload<int>::of(&QSpinBox::valueChanged),
            this,[this]() {setupMatrixSize(matrixLayout2,
                           rowSpin2->value(), colSpin2->value());});
    connect(processButton, &QPushButton::clicked,
            this,&MathResult::processMatrix);

    setupOperationInterface();
    updateInterface();
    showFullScreen();
}
void MathResult::updateInterface(){
    bool showSecondMatrix = (currentOperationType == 2);
    matrix2Widget->setVisible(showSecondMatrix);
    
    setupOperationInterface();
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

void MathResult::setupMatrixSize(QGridLayout* gridLayout, int rows, int cols) {
    clearLayout(gridLayout);

    gridLayout->setSpacing(15);
    gridLayout->setHorizontalSpacing(20);
    gridLayout->setVerticalSpacing(15);
    gridLayout->setAlignment(Qt::AlignCenter);

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            QLineEdit* edit = new QLineEdit(this);
            edit->setAlignment(Qt::AlignCenter);
            edit->setText("0");
            edit->setFixedSize(70, 35);
            gridLayout->addWidget(edit, r, c);
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

void MathResult::processMatrix() {
    Matrix matrix1 = readMatrixFromLayout(matrixLayout,
    rowSpin->value(), colSpin->value());
    QString resultText;

    switch(currentOperationType){
    case 0:
        resultText = processDeterminant(matrix1);
        break;
    case 1:
        resultText = processInverseMatrix(matrix1);
        break;
    case 2:
        {
            Matrix matrix2 = readMatrixFromLayout(matrixLayout2,
            rowSpin2->value(), colSpin2->value());
            resultText = processMatrixOperations(matrix1, matrix2);
        }
        break;
    case 3:
        resultText = processTranspose(matrix1);
        break;
    case 4:
        resultText = processTriangleForm(matrix1);
        break;
    }

    resultLabel->setText(resultText);
    resultLabel->setAlignment(Qt::AlignCenter);
}

Matrix MathResult::readMatrixFromLayout(QGridLayout* layout, int rows, int cols){
    Matrix matrix(rows, cols);
    for (int r = 0; r < rows; ++r){
        for (int c = 0; c < cols; ++c){
            QLayoutItem* item = layout->itemAtPosition(r, c);
            if (!item || !item->widget()) continue;

            QLineEdit* edit = qobject_cast<QLineEdit*>(item->widget());
            if (!edit) continue;

            QString text = edit->text();
            matrix(r, c) = atoFrc(text.toStdString());
        }
    }
    return matrix;
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

QString MathResult::processMatrixOperations(Matrix& matrix1, Matrix& matrix2) {
    QString result;


    result += "A: " + QString::number(matrix1.getRows()) + "x" + QString::number(matrix1.getCols());
    result += "    ";
    result += "B: " + QString::number(matrix2.getRows()) + "x" + QString::number(matrix2.getCols());

    int maxRows = std::max(matrix1.getRows(), matrix2.getRows());


    for (int r = 0; r < maxRows; ++r) {
        // Строка матрицы A
        if (r < matrix1.getRows()) {
            result += "[ ";
            for (int c = 0; c < matrix1.getCols(); ++c) {
                Fraction frac = matrix1(r, c);
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
            result += "]";
        } else {
            // Пустое место если строк в матрице A меньше
            result += QString(" ").repeated(matrix1.getCols() * 8);
        }

        // Разделитель между матрицами
        result += "    "; // Отступ между матрицами

        // Строка матрицы B
        if (r < matrix2.getRows()) {
            result += "[ ";
            for (int c = 0; c < matrix2.getCols(); ++c) {
                Fraction frac = matrix2(r, c);
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
            result += "]";
        }

        result += "\n";
    }


    result += "\n\nОперации с матрицами (в разработке)";
    return result;
}

void MathResult::clearLayout(QLayout* layout) {
    if (!layout) return;

    QLayoutItem* item;
    while ((item = layout->takeAt(0))) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}
