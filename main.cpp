#include <QApplication>
#include "mainwindow.h"
#include <random>
#include <QtGlobal>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QVector<QVector<int>> adjList;
    for (int i = 0; i < 10; ++i) {
        QVector<int> neigh;
        for (int j = 1 - (i % 2); j < 10; j+=2)
            neigh.push_back(j);
        adjList.push_back(neigh);
    }
    MainWindow window;
    //window.setGeometry(50, 50, 400, 200);
    window.setGraph(adjList);
    window.show();

//    GraphWidget gw;
//    gw.setGeometry(50, 50, 500, 500);
//    gw.setGraph(adjList);
//    gw.show();
    return app.exec();
}
