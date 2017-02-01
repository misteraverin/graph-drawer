#ifndef GRAPH_WIDGET_H
#define GRAPH_WIDGET_H
#include <QPointF>
#include <QVector>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QtGlobal>

class GraphWidget : public QWidget
{
    Q_OBJECT
private:
    int vertexNumber, edgeNumber;
    QVector<QVector<int>> adjacencyList;
    // coordinates of the vertices on plane, vertices are in the same order as in adjacency list
    QVector<QPointF> coordinates;
    bool waitForClick;
    bool hasDrawn;
    void drawGraph();
protected:
    void paintEvent(QPaintEvent *ev) override;
public:
    // generate random points in size * size square
    // WARNING: always produces the same result when using MinGW
    static QVector<QPointF> genRandomPoints(int n, float size);
    static int maxVertexNumber;
    int getVertexNumber() const;
    int getEdgeNumber() const;
    void setGraph(QVector<QVector<int>>);
    void setWaitForClick(bool);
    void setCoordinates(QVector<QPointF> coords);
    GraphWidget(QWidget *parent = 0);
public slots:
    void drawOnClick();
};

#endif // GRAPH_WIDGET_H
