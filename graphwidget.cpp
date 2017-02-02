#include "graphwidget.h"

int GraphWidget::matrixSize = 40;

QVector<QPoint> GraphWidget::genRandomPoints(int n, int size) {
    qInfo() << "size " << size << endl;
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> dis(0, size - 1);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    QVector<QPoint> points;
    for (int i = 0; i < n; ++i) {
        points.push_back(QPoint(qrand() % size, qrand() % size));
    }
    return points;
}


GraphWidget::GraphWidget(QWidget* parent) : QWidget(parent)
{
    gotFinalCoordinates = 0;
    vertexNumber = 0;
    edgeNumber = 0;
    waitForClick = false;
    setStyleSheet("background-color:white;");
}

void GraphWidget::paintEvent(QPaintEvent* ) {
    qInfo() << "received paint event" << endl;
    qInfo() << gotFinalCoordinates << endl;
    if (!waitForClick || gotFinalCoordinates) {
        qInfo() << "drawing graph..." << endl;
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        for (int i = 0; i < vertexNumber; ++i) {
            QVector<int> neighbours = adjacencyList[i];
            for (int j = 0; j < neighbours.size(); ++j) {
                int v = neighbours[j];
                if (v > i) {
                    painter.drawLine(QLineF(coordinates[v], coordinates[i]));
                }
            }
        }
    }
}

void GraphWidget::drawOnClick() {
    if (waitForClick && !gotFinalCoordinates) {
        qInfo() << "received click signal" << endl;
        setCoordinates(genRandomPoints(vertexNumber, matrixSize));
        update();
    }
}


void GraphWidget::setGraph(QVector<QVector<int>> adjList) {
    adjacencyList = adjList;
    vertexNumber = adjList.size();
    qInfo() << "height " << size().height() << endl;
    if (!waitForClick) {
        setCoordinates(genRandomPoints(vertexNumber, matrixSize));
    }
}


void GraphWidget::setCoordinates(QVector<QPoint> coords) {
    if (!adjacencyList.isEmpty()) {
        if (coords.size() != adjacencyList.size()) {
            qWarning() << "incorrect params passed to GraphWidget: sizes of coordinates vector and adjacency list differ";
            return;
        }
        qInfo() << "size of widget " << size().width() << ' ' << size().height() << endl;
        float coef = size().height() / matrixSize;
        for (int i = 0; i < coords.size(); ++i) {
            coordinates.push_back(QPoint((coords[i].ry() + .5) * coef, (coords[i].rx() + .5) * coef));
        }
        if (waitForClick)
            gotFinalCoordinates = 1;
        return;
    }

    qWarning() << "attempt to set coordinates when graph is not set";
}

void GraphWidget::setWaitForClick(bool wfc) {
    waitForClick = wfc;
}
