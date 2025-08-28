#ifndef GEOMETRYRESULT_H
#define GEOMETRYRESULT_H

#include <QWidget>
#include <QStackedWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include "geometry/Triangle/trianglegraphic.hpp"
#include "geometry/Triangle/triangle.hpp"
#include "geometry/Tetragon/tetragongraphic.hpp"
#include "geometry/Tetragon/tetragon.hpp"

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
    void updateTetragonInfo();

private:
    QFormLayout* formLayout;

    QStackedWidget *stackedWidget;
    TriangleGraphic *triangleGraphic;
    TetragonGraphic *tetragonGraphic;

    QLineEdit *axEdit, *ayEdit, *bxEdit, *byEdit, *cxEdit, *cyEdit, *dxEdit, *dyEdit;
    QLabel *infoLabel;

    QWidget* createTriangleWidget();
    QWidget* createTetragonWidget();
    QWidget* createEllipseWidget();
    QWidget* createPolygonWidget();
};

#endif
