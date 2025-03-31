#ifndef TRIANGLEGRAPHIC_H
#define TRIANGLEGRAPHIC_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QWheelEvent>

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
    struct Point { float x, y; } triangle[3];
    float zoom = 1.0f;
    QPointF offset;
    const float pixelToCoord = 0.1f; // Масштабный коэффициент (10 пикселей = 1 единица координат)

    void drawGrid();
    void drawAxes();
    void drawTriangle();
    void applyTransformations();
};

#endif // TRIANGLEGRAPHIC_H
