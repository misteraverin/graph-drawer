#ifndef GRAPH_WIDGET_H
#define GRAPH_WIDGET_H
#include <QPointF>
#include <QPoint>
#include <QVector>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QtGlobal>
#include <QTime>

class GraphWidget : public QWidget
{
    Q_OBJECT
private:
    int vertexNumber, edgeNumber;
    QVector<QVector<int>> adjacencyList;
    // coordinates of the vertices on plane, vertices are in the same order as in adjacency list
    QVector<QPointF> coordinates;
    bool waitForClick;
    bool gotFinalCoordinates;
protected:
    void paintEvent(QPaintEvent *ev) override;
public:
    // generate random points in size * size matrix
    // WARNING: always produces the same result when using MinGW
    static QVector<QPoint> genRandomPoints(int n, int size);
    static int matrixSize;
    int getVertexNumber() const;
    int getEdgeNumber() const;
    void setGraph(QVector<QVector<int>>);
    void setWaitForClick(bool);
    // takes coordinates in (row, column) format
    void setCoordinates(QVector<QPoint> coords);
    GraphWidget(QWidget *parent = 0);
public slots:
    void drawOnClick();
};

#endif // GRAPH_WIDGET_H
