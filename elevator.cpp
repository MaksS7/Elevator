#include "elevator.h"
#include "ui_elevator.h"
#include <QGraphicsScene>
#include <QGraphicsItem>

Elevator::Elevator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Elevator)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    cabine *cab = new cabine;
    scene->addItem(cab);
    ui->graphicsView->setScene(scene);
}

Elevator::~Elevator()
{
    delete ui;
}

