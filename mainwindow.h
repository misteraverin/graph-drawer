#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsAnchorLayout>
#include <QGraphicsLinearLayout>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QGraphicsProxyWidget>
#include <QGridLayout>
#include "graphwidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    QPushButton *button;
    GraphWidget *initialRepresentation;
    GraphWidget *finalRepresentation;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setGraph(QVector<QVector<int>>);
signals:

public slots:
};

#endif // MAINWINDOW_H
