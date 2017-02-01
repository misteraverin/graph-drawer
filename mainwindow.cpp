#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setGeometry(50, 50, 800, 450);
    button = new QPushButton("Evolve!", this);
    QGraphicsScene scene;
//    scene.addWidget(this);
    scene.setSceneRect(geometry());
    QGraphicsProxyWidget* gButton = scene.addWidget(button);
    QGraphicsLinearLayout* verticalLayout = new QGraphicsLinearLayout;
    verticalLayout->setOrientation(Qt::Vertical);
    initialRepresentation = new GraphWidget(this);
    finalRepresentation = new GraphWidget(this);
    QGraphicsLinearLayout* horizontalLayout = new QGraphicsLinearLayout;
    initialRepresentation->setBaseSize(400, 400);
    finalRepresentation->setBaseSize(400, 400);
    QGraphicsProxyWidget* gInitialRepresentation = scene.addWidget(initialRepresentation);
    QGraphicsProxyWidget* gFinalRepresentation = scene.addWidget(finalRepresentation);
    horizontalLayout->addItem(gInitialRepresentation);
    horizontalLayout->addItem(gFinalRepresentation);
//    initialRepresentation->setGeometry(0, 0, 400, 400);
//    finalRepresentation->setGeometry(400, 0, 400, 400);
    verticalLayout->addItem(horizontalLayout);
    verticalLayout->addItem(gButton);
    setLayout(verticalLayout);
    qInfo() << initialRepresentation->size().width() << " " << initialRepresentation->size().height() << endl;
//    finalRepresentation->setWaitForClick(1);
    connect(button, &QPushButton::clicked, finalRepresentation, &GraphWidget::drawOnClick);

}

void MainWindow::setGraph(QVector<QVector<int> > adjList) {
    initialRepresentation->setGraph(adjList);
//    initialRepresentation->setCoordinates(GraphWidget::genRandomPoints(adjList.size(), initialRepresentation->baseSize().width()));
    finalRepresentation->setGraph(adjList);
//    finalRepresentation->setCoordinates(GraphWidget::genRandomPoints(adjList.size(), finalRepresentation->baseSize().width()));
}
