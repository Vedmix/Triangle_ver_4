#include "trianglegraphic.h"
#include <cmath>

TriangleGraphic::TriangleGraphic(QWidget *parent)
    : QOpenGLWidget(parent), offset(0, 0)
{
    setFocusPolicy(Qt::StrongFocus);
    resetView();
}

void TriangleGraphic::setTriangleCoordinates(float ax, float ay, float bx, float by, float cx, float cy) {
    triangle[0] = {ax, ay};
    triangle[1] = {bx, by};
    triangle[2] = {cx, cy};
    update();
}

void TriangleGraphic::resetView() {
    zoom = 1.0f;
    offset = QPointF(0, 0);
    update();
}

void TriangleGraphic::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TriangleGraphic::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void TriangleGraphic::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    applyTransformations();

    drawGrid();
    drawAxes();
    drawTriangle();
}

void TriangleGraphic::applyTransformations() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = float(width()) / height();
    float visibleWidth = (width() * pixelToCoord) / zoom;
    float visibleHeight = (height() * pixelToCoord) / zoom;

    if (aspect > 1.0f) {
        glOrtho(-visibleWidth/2 + offset.x(), visibleWidth/2 + offset.x(),
                -visibleHeight/2 + offset.y(), visibleHeight/2 + offset.y(),
                -1, 1);
    } else {
        glOrtho(-visibleWidth/2 + offset.x(), visibleWidth/2 + offset.x(),
                -visibleHeight/2 + offset.y(), visibleHeight/2 + offset.y(),
                -1, 1);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void TriangleGraphic::drawGrid() {
    glColor3f(0.9f, 0.9f, 0.9f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);

    // Рассчитываем видимую область
    float left = (-width()/2 * pixelToCoord)/zoom + offset.x();
    float right = (width()/2 * pixelToCoord)/zoom + offset.x();
    float bottom = (-height()/2 * pixelToCoord)/zoom + offset.y();
    float top = (height()/2 * pixelToCoord)/zoom + offset.y();

    // Рисуем сетку с шагом 1 единица
    for (float x = floor(left); x <= ceil(right); x += 1.0f) {
        glVertex2f(x, bottom);
        glVertex2f(x, top);
    }

    for (float y = floor(bottom); y <= ceil(top); y += 1.0f) {
        glVertex2f(left, y);
        glVertex2f(right, y);
    }

    glEnd();
}

void TriangleGraphic::drawAxes() {
    glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    // Рассчитываем видимую область
    float left = (-width()/2 * pixelToCoord)/zoom + offset.x();
    float right = (width()/2 * pixelToCoord)/zoom + offset.x();
    float bottom = (-height()/2 * pixelToCoord)/zoom + offset.y();
    float top = (height()/2 * pixelToCoord)/zoom + offset.y();

    // Ось X
    glVertex2f(left, 0);
    glVertex2f(right, 0);

    // Ось Y
    glVertex2f(0, bottom);
    glVertex2f(0, top);

    // Стрелки осей
    float arrowSize = 0.5f;
    glVertex2f(right - arrowSize, arrowSize);
    glVertex2f(right, 0);
    glVertex2f(right - arrowSize, -arrowSize);
    glVertex2f(right, 0);

    glVertex2f(arrowSize, top - arrowSize);
    glVertex2f(0, top);
    glVertex2f(-arrowSize, top - arrowSize);
    glVertex2f(0, top);

    glEnd();
}

void TriangleGraphic::drawTriangle() {
    // Линии треугольника
    glColor3f(0.0f, 0.7f, 0.0f);
    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(triangle[0].x, triangle[0].y);
    glVertex2f(triangle[1].x, triangle[1].y);
    glVertex2f(triangle[2].x, triangle[2].y);
    glEnd();

    // Вершины треугольника
    glColor3f(0.8f, 0.0f, 0.8f);
    glPointSize(7.0f);
    glBegin(GL_POINTS);
    glVertex2f(triangle[0].x, triangle[0].y);
    glVertex2f(triangle[1].x, triangle[1].y);
    glVertex2f(triangle[2].x, triangle[2].y);
    glEnd();
}

void TriangleGraphic::keyPressEvent(QKeyEvent *event) {
    const float moveStep = 1.0f;

    switch (event->key()) {
    case Qt::Key_Plus:
    case Qt::Key_Equal:
        zoom *= 1.1f;
        break;
    case Qt::Key_Minus:
        zoom /= 1.1f;
        break;
    case Qt::Key_W:
        offset.ry() -= moveStep;
        break;
    case Qt::Key_S:
        offset.ry() += moveStep;
        break;
    case Qt::Key_A:
        offset.rx() += moveStep;
        break;
    case Qt::Key_D:
        offset.rx() -= moveStep;
        break;
    case Qt::Key_R:
        resetView();
        break;
    }

    update();
}

void TriangleGraphic::wheelEvent(QWheelEvent *event) {
    QPoint numDegrees = event->angleDelta() / 8;
    if (!numDegrees.isNull()) {
        zoom *= (numDegrees.y() > 0) ? 1.1f : 0.9f;
        update();
    }
    event->accept();
}
