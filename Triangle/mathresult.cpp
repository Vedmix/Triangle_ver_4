#include "mathresult.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QApplication>
#include <QScreen>
#include <QKeyEvent>
#include <QScreen>

MathResult::MathResult(int contentIndex, QWidget *parent)
    : QWidget(parent),
      stackedWidget(new QStackedWidget(this)),
      resultLabel(new QLabel("Введите матрицу и нажмите кнопку", this)),
      processButton(new QPushButton("Показать матрицу", this)),
      rowSpin(new QSpinBox(this)),
      colSpin(new QSpinBox(this))
{
    setStyleSheet("background-color: white;");
    setStyleSheet("QLabel { color: black; font-weight: bold; }");



    // Инициализация matrixLayout как дочернего элемента this
    matrixLayout = new QGridLayout();

    // Настройка элементов
    rowSpin->setRange(1, 10);
    colSpin->setRange(1, 10);
    rowSpin->setValue(3);
    colSpin->setValue(3);

    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setStyleSheet("QLabel { color: black; font-weight: bold; }");

    // Главная компоновка
    QVBoxLayout* mainLayout = new QVBoxLayout(this);  // Устанавливаем layout для this

    // Горизонтальная компоновка для элементов управления
    QHBoxLayout* controlLayout = new QHBoxLayout();  // Не устанавливаем родителя!
    controlLayout->addWidget(new QLabel("Строки:"));
    controlLayout->addWidget(rowSpin);
    controlLayout->addWidget(new QLabel("Столбцы:"));
    controlLayout->addWidget(colSpin);

    // Добавляем все элементы в главный layout
    mainLayout->addWidget(resultLabel);
    mainLayout->addLayout(matrixLayout);  // Добавляем grid layout
    mainLayout->addLayout(controlLayout); // Добавляем control layout
    mainLayout->addWidget(processButton);

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

    // Добавляем заголовок
    result += "Матрица " + QString::number(rows) + "x" + QString::number(cols) + ":\n";
    result += "----------------\n";

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            Fraction frac = matrix(r, c);

            // Форматируем дробь
            if (frac.getDown() == 1) {
                result += QString::number(frac.getUp());
            } else {
                // Для отрицательных дробей правильно размещаем знак
                if (frac.getUp() < 0 || frac.getDown() < 0) {
                    result += "-" + QString::number(abs(frac.getUp())) + "/" + QString::number(abs(frac.getDown()));
                } else {
                    result += QString::number(frac.getUp()) + "/" + QString::number(frac.getDown());
                }
            }

            // Добавляем отступ между элементами
            result += "\t";
        }
        result += "\n"; // Новая строка матрицы
    }

    // Добавляем информацию о детерминанте для квадратных матриц
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
    // Очищаем текущие элементы
    QLayoutItem* child;
    while ((child = matrixLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            delete child->widget();
        }
        delete child;
    }

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

    // Вывод матрицы с черным цветом текста
    resultLabel->setText(matrixToString(matrix));
    resultLabel->setStyleSheet("QLabel { color: black; font-weight: bold; }");
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


