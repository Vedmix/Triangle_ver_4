#ifndef GEOMETRYWINDOW_H
#define GEOMETRYWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class GeometryWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GeometryWindow(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void openGeometryResult();

private:
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QVBoxLayout *buttonLayout;
};

#endif
