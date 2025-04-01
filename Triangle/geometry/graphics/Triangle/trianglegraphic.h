#ifndef TRIANGLEGRAPHIC_H
#define TRIANGLEGRAPHIC_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QPointF>

class TriangleGraphic : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit TriangleGraphic(QWidget *parent = nullptr);
    void setTriangleCoordinates(float ax, float ay, float bx, float by, float cx, float cy);
    void resetView();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    struct Point { float x, y; };
    Point triangle[3];
    QPointF offset;
    float zoom;
    const float pixelToCoord = 0.1f;

    void drawGrid();
    void drawAxes();
    void drawTriangle();
    void applyTransformations();
};

#endif
