#ifndef TRIANGLEGRAPHIC_H
#define TRIANGLEGRAPHIC_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class TriangleGraphic : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit TriangleGraphic(QWidget *parent = nullptr);
    void setTriangleCoordinates(double ax, double ay, double bx, double by, double cx, double cy);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    double ax, ay, bx, by, cx, cy;
    int winW, winH;
    float scale;
    float posX, posY;

    void drawGrid();
    void drawAxes();
    void drawTriangle();
};

#endif // TRIANGLEGRAPHIC_H
