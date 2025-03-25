#ifndef GEOMETRYRESULT_H
#define GEOMETRYRESULT_H

#include <QWidget>
#include <QStackedWidget>

class GeometryResult : public QWidget
{
    Q_OBJECT
public:
    explicit GeometryResult(int contentIndex, QWidget *parent = nullptr);
    ~GeometryResult() = default;

private:
    QStackedWidget *stackedWidget;

    QWidget* createTriangleWidget();
    QWidget* createTetragonWidget();
    QWidget* createEllipseWidget();
    QWidget* createPolygonWidget();

    void showTriangleContent();
    void showTetragonContent();
    void showEllipseContent();
    void showPolygonContent();

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif
