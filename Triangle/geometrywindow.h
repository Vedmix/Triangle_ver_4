#ifndef GEOMETRYWINDOW_H
#define GEOMETRYWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class GeometryWindow : public QWidget {
    Q_OBJECT
protected:
    void keyPressEvent(QKeyEvent *event);
public:
    explicit GeometryWindow(QWidget *parent = nullptr);
};

#endif // GEOMETRYWINDOW_H
