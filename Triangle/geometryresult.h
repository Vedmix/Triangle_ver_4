#ifndef GEOMETRYRESULT_H
#define GEOMETRYRESULT_H

#include <QWidget>
#include <QStackedWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include "geometry/graphics/Triangle/trianglegraphic.h"
#include "geometry/graphics/Triangle/triangle.h"

class GeometryResult : public QWidget
{
    Q_OBJECT

public:
    explicit GeometryResult(int contentIndex = 0, QWidget *parent = nullptr);
    ~GeometryResult() = default;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateTriangleInfo();

private:
    QFormLayout* formLayout;

    QStackedWidget *stackedWidget;
    TriangleGraphic *triangleGraphic;

    QLineEdit *axEdit, *ayEdit, *bxEdit, *byEdit, *cxEdit, *cyEdit;
    QLabel *infoLabel;

    QWidget* createTriangleWidget();
    QWidget* createTetragonWidget();
    QWidget* createEllipseWidget();
    QWidget* createPolygonWidget();
};

#endif // GEOMETRYRESULT_H
