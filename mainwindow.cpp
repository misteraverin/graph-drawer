#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setGeometry(50, 50, 850, 450);
    button = new QPushButton("Evolve!", this);
    initialRepresentation = new GraphWidget(this);
    finalRepresentation = new GraphWidget(this);
    initialRepresentation->setGeometry(0, 0, 400, 400);
    finalRepresentation->setGeometry(400, 0, 400, 400);
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(initialRepresentation, 0, 0);
    layout->addWidget(finalRepresentation, 0, 1);
    layout->addWidget(button, 1, 0, Qt::AlignHCenter);
    setLayout(layout);
    dumpObjectTree();
    qInfo() << initialRepresentation->size().width() << " " << initialRepresentation->size().height() << endl;
    finalRepresentation->setWaitForClick(1);
    connect(button, &QPushButton::clicked, finalRepresentation, &GraphWidget::drawOnClick);

}

MainWindow::~MainWindow() {
}

void MainWindow::setGraph(QVector<QVector<int> > adjList) {
    initialRepresentation->setGraph(adjList);
    finalRepresentation->setGraph(adjList);
}
