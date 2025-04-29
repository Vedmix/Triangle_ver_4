#include "tetragongraphic.h"
#include <cmath>

TetragonGraphic::TetragonGraphic(QWidget *parent)
    : QOpenGLWidget(parent), offset(0, 0), zoom(1.0f)
{
    setFocusPolicy(Qt::StrongFocus);
    resetView();
}

void TetragonGraphic::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TetragonGraphic::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void TetragonGraphic::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    applyTransformations();
    drawGrid();
    drawAxes();
    drawTetragon();
}

void TetragonGraphic::setTetragonCoordinates(float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy)
{
    tetragon[0] = {ax, ay};
    tetragon[1] = {bx, by};
    tetragon[2] = {cx, cy};
    tetragon[3] = {dx, dy};
    update();
}

void TetragonGraphic::resetView()
{
    zoom = 1.0f;
    offset = QPointF(0, 0);
    update();
}

void TetragonGraphic::applyTransformations()
{
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


void TetragonGraphic::drawGrid()
{
    glColor3f(0.9f, 0.9f, 0.9f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);

    float left = (-width()/2 * pixelToCoord)/zoom + offset.x();
    float right = (width()/2 * pixelToCoord)/zoom + offset.x();
    float bottom = (-height()/2 * pixelToCoord)/zoom + offset.y();
    float top = (height()/2 * pixelToCoord)/zoom + offset.y();

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

void TetragonGraphic::drawAxes()
{
    glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    float left = (-width()/2 * pixelToCoord)/zoom + offset.x();
    float right = (width()/2 * pixelToCoord)/zoom + offset.x();
    float bottom = (-height()/2 * pixelToCoord)/zoom + offset.y();
    float top = (height()/2 * pixelToCoord)/zoom + offset.y();

    glVertex2f(left, 0);
    glVertex2f(right, 0);
    glVertex2f(0, bottom);
    glVertex2f(0, top);

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

void TetragonGraphic::drawTetragon()
{
    glColor3f(0.0f, 0.7f, 0.0f);
    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(tetragon[0].x, tetragon[0].y);
    glVertex2f(tetragon[1].x, tetragon[1].y);
    glVertex2f(tetragon[2].x, tetragon[2].y);
    glVertex2f(tetragon[3].x, tetragon[3].y);
    glEnd();

    glColor3f(0.8f, 0.0f, 0.8f);
    glPointSize(7.0f);
    glBegin(GL_POINTS);
    glVertex2f(tetragon[0].x, tetragon[0].y);
    glVertex2f(tetragon[1].x, tetragon[1].y);
    glVertex2f(tetragon[2].x, tetragon[2].y);
    glVertex2f(tetragon[3].x, tetragon[3].y);
    glEnd();
}

void TetragonGraphic::keyPressEvent(QKeyEvent *event)
{
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

void TetragonGraphic::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta() / 8;
    if (!numDegrees.isNull()) {
        zoom *= (numDegrees.y() > 0) ? 1.1f : 0.9f;
        update();
    }
    event->accept();
}
