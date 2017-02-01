#include "graphwidget.h"
#include <iostream>
int GraphWidget::maxVertexNumber = 128;

QVector<QPointF> GraphWidget::genRandomPoints(int n, float size) {
    qInfo() << "size " << size << endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, size);
    QVector<QPointF> points;
    for (int i = 0; i < n; ++i) {
        points.push_back(QPointF(dis(gen), dis(gen)));
        qInfo() << points[i].rx() << ' ' << points[i].ry() << endl;
    }
    return points;
}


GraphWidget::GraphWidget(QWidget* parent) : QWidget(parent)
{

    hasDrawn = 0;
    vertexNumber = 0;
    edgeNumber = 0;
    waitForClick = false;
    setStyleSheet("background-color:white;");
}

void GraphWidget::paintEvent(QPaintEvent* ) {
    qInfo() << "received paint event" << endl;
    if (!waitForClick)
        drawGraph();
}

void GraphWidget::drawOnClick() {
    qInfo() << "received clicked signal" << endl;
    drawGraph();
}

void GraphWidget::drawGraph() {
    qInfo() << "drawing graph..." << endl;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (int i = 0; i < vertexNumber; ++i) {
        QVector<int> neighbours = adjacencyList[i];
        for (int j = 0; j < neighbours.size(); ++j) {
            int v = neighbours[j];
            if (v > i) {
                painter.drawLine(QLineF(coordinates[v], coordinates[i]));
//                qInfo() << "drawing edge between vertices " << v << " " << i << endl;
            }
        }
    }
    hasDrawn = 1;
}

void GraphWidget::setGraph(QVector<QVector<int>> adjList) {
    adjacencyList = adjList;
    vertexNumber = adjList.size();
    qInfo() << "height " << size().height() << endl;
    setCoordinates(genRandomPoints(vertexNumber, size().height()));
}

void GraphWidget::setCoordinates(QVector<QPointF> coords) {
    if (!adjacencyList.isEmpty()) {
        if (coords.size() != adjacencyList.size()) {
            qWarning() << "incorrect params passed to GraphWidget: sizes of coordinates vector and adjacency list differ";
            return;
        }
        coordinates = coords;
//        drawGraph();
        return;
    }
    qWarning() << "attempt to set coordinates when graph is not set";
}

void GraphWidget::setWaitForClick(bool wfc) {
    waitForClick = wfc;
}
