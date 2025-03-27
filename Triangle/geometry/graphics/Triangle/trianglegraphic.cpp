#include "trianglegraphic.h"
#include <QKeyEvent>

TriangleGraphic::TriangleGraphic(QWidget *parent)
    : QOpenGLWidget(parent), winW(1000), winH(1000), scale(1.0), posX(0.0), posY(0.0)
{
    setFocusPolicy(Qt::StrongFocus);
}

void TriangleGraphic::setTriangleCoordinates(double ax, double ay, double bx, double by, double cx, double cy) {
    this->ax = ax;
    this->ay = ay;
    this->bx = bx;
    this->by = by;
    this->cx = cx;
    this->cy = cy;
    update();
}

void TriangleGraphic::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TriangleGraphic::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    winW = w;
    winH = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w/2, w/2, -h/2, h/2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void TriangleGraphic::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(posX, posY, 0);
    glScalef(scale, scale, 1);

    drawGrid();
    drawAxes();
    drawTriangle();
}

void TriangleGraphic::drawGrid() {
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (float i = -winW/2; i <= winW/2; i += 10) {
        glVertex2f(i, -winH/2);
        glVertex2f(i, winH/2);
        glVertex2f(-winW/2, i);
        glVertex2f(winW/2, i);
    }
    glEnd();
}

void TriangleGraphic::drawAxes() {
    glColor3f(0.7f, 0.7f, 0.7f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(-winW/2, 0);
    glVertex2f(winW/2, 0);
    glVertex2f(0, -winH/2);
    glVertex2f(0, winH/2);
    glEnd();
}

void TriangleGraphic::drawTriangle() {
    // Рисуем линии треугольника
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(ax * 10, ay * 10);
    glVertex2f(bx * 10, by * 10);
    glVertex2f(cx * 10, cy * 10);
    glEnd();

    // Рисуем вершины треугольника
    glColor3f(1.0f, 0.0f, 1.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(ax * 10, ay * 10);
    glVertex2f(bx * 10, by * 10);
    glVertex2f(cx * 10, cy * 10);
    glEnd();
}
