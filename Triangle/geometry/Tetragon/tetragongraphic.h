#ifndef TETRAGONGRAPHIC_H
#define TETRAGONGRAPHIC_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QPointF>

class TetragonGraphic : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit TetragonGraphic(QWidget *parent = nullptr);
    void setTetragonCoordinates(float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy);
    void resetView();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    struct Point { float x, y; };
    Point tetragon[4];
    QPointF offset;
    float zoom;
    const float pixelToCoord = 0.1f;

    void drawGrid();
    void drawAxes();
    void drawTetragon();
    void applyTransformations();
};

#endif
