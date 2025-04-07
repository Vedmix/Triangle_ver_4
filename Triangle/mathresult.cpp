#include "mathresult.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QApplication>
#include <QScreen>
#include <QKeyEvent>
#include <QSpacerItem>

MathResult::MathResult(int contentIndex, QWidget *parent)
    : QWidget(parent),
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
        }
        QLineEdit {
            background-color: white;
            border: 1px solid gray;
        }
    )");

    // Главный вертикальный layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    // Первый спейсер для выравнивания по вертикали
    mainLayout->addStretch(1);

    // Горизонтальный layout для центрирования содержимого
    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addStretch(1);

    // Вертикальный layout для матрицы и элементов управления
    QVBoxLayout* vLayout = new QVBoxLayout();

    // Настройка элементов управления
    rowSpin->setRange(1, 10);
    colSpin->setRange(1, 10);
    rowSpin->setValue(3);
    colSpin->setValue(3);

    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setMinimumWidth(400); // Фиксированная ширина для выравнивания

    // Layout для контролов размера матрицы
    QHBoxLayout* controlLayout = new QHBoxLayout();
    controlLayout->addWidget(new QLabel("Строки:"));
    controlLayout->addWidget(rowSpin);
    controlLayout->addWidget(new QLabel("Столбцы:"));
    controlLayout->addWidget(colSpin);

    // Layout для матрицы
    matrixLayout = new QGridLayout();
    matrixLayout->setAlignment(Qt::AlignCenter);

    // Добавляем элементы в вертикальный layout
    vLayout->addWidget(resultLabel, 0, Qt::AlignCenter);
    vLayout->addLayout(controlLayout);
    vLayout->addLayout(matrixLayout);
    vLayout->addWidget(processButton, 0, Qt::AlignCenter);

    // Добавляем вертикальный layout в горизонтальный
    hLayout->addLayout(vLayout);
    hLayout->addStretch(1);

    // Добавляем горизонтальный layout в главный
    mainLayout->addLayout(hLayout);

    // Второй спейсер для выравнивания по вертикали
    mainLayout->addStretch(1);

    // Подключение сигналов
    connect(rowSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MathResult::updateMatrixSize);
    connect(colSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MathResult::updateMatrixSize);
    connect(processButton, &QPushButton::clicked,
            this, &MathResult::processMatrix);

    updateMatrixSize();
    showFullScreen();
}


QWidget* MathResult::createDeterminatorRank() {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(new QLabel("Определитель / Ранг матрицы (в разработке)"));
    return widget;
}

QWidget* MathResult::createTranspose() {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(new QLabel("Транспонирование матрицы (в разработке)"));
    return widget;
}

QWidget* MathResult::createInverseMatrix() {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(new QLabel("Обратная матрица (в разработке)"));
    return widget;
}

QWidget* MathResult::createMatrixOperations() {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(new QLabel("Действия с матрицами (*, +, -, *k) (в разработке)"));
    return widget;
}

QString MathResult::matrixToString(Matrix& matrix) const {
    QString result;
    int rows = matrix.getRows();
    int cols = matrix.getCols();

    result += "Матрица " + QString::number(rows) + "x" + QString::number(cols) + ":\n";
    result += "----------------\n";

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

    if (rows == cols) {
        try {
            Fraction det = matrix.determinant();
            result += "\nОпределитель: ";
            if (det.getDown() == 1) {
                result += QString::number(det.getUp());
            } else {
                result += QString::number(det.getUp()) + "/" + QString::number(det.getDown());
            }
        } catch (...) {
            result += "\nНе удалось вычислить определитель";
        }
    }

    return result;
}

void MathResult::ImplataMatrixSize() {
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
    ImplataMatrixSize();
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

    resultLabel->setText(matrixToString(matrix));
    resultLabel->setAlignment(Qt::AlignCenter); // Центрируем текст результата
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
