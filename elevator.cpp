#include "elevator.h"
#include "ui_elevator.h"
#include <QDebug>

Elevator::Elevator(QWidget *parent)
    : QMainWindow(parent)
    , duration(2000)
    , heightCabine(10)
    , widthCabine(10)
    , floorCount(5)
    , startPosition(10, 10, widthCabine, heightCabine)
    , currentPosition(startPosition)
    , cab(nullptr)
    , ui(new Ui::Elevator)
{
    ui->setupUi(this);
    ui->spinBoxFloorCount->setValue(5);
    //TODO: Добавить генерацию сцены от количесвта этажей
    //TODO: Добавить автоматическую генерацию кнопок по этажам
    //TODO: Добавить текущее положение лифта
    //TODO: Добавить индикацию движения лифта
    cab = new cabine(startPosition);

    ui->graphicsView->setSceneRect(QRectF(0,0, 100, 300));
    scene = new QGraphicsScene(this);
    scene->addItem(cab);
    ui->graphicsView->setScene(scene);
    animation = new QPropertyAnimation(cab, "geometry");

    connect(ui->btnStart, &QPushButton::clicked, this, &Elevator::startAnimation);
    connect(ui->btnReset, &QPushButton::clicked, this, &Elevator::resetPosition);
    connect(ui->spinBoxFloorCount, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &Elevator::setFloorCount);
    connect(animation, &QPropertyAnimation::finished, [this] (){currentPosition = nextPosition;});

    addFloor(floorCount);
}

Elevator::~Elevator()
{
    for (auto &item : buttonVector) {
        delete item;
    }
    delete cab;
    delete scene;
    delete animation;
    delete ui;
}

void Elevator::startAnimation()
{
    animation->setDuration(duration);
//    animation->setStartValue(startPosition);
    animation->setEndValue(nextPosition);
    animation->start();
}

void Elevator::resetPosition()
{
    if (cab != nullptr) {
        cab->setGeometry(startPosition);
        scene->update();
    }
}

void Elevator::setNextPosition(const QRectF &position)
{
    nextPosition = position;
}

void Elevator::setFloorCount(int8_t count)
{
    floorCount = count;
}

int8_t Elevator::getFloorCount() const
{
    return floorCount;
}

void Elevator::addFloor(int count)
{
    if (!buttonVector.isEmpty()) {
        for (auto &item : buttonVector) {
            delete item;
        }
    }
    for (int i(count - 1); i >= 0 ; i--) {
        btn = new QPushButton(QString::number(i + 1));
        buttonVector.push_back(btn);
//        if (!i) {
//            connect(btn, QOverload<bool>::of(&QPushButton::clicked),
//                    [this] (bool checked) {setNextPosition(startPosition);});
//            floorPosition.push_back(startPosition);
//        } else {

            QRectF tempRect = startPosition;
            tempRect.moveTop(heightCabine * (3 * (i))); //TODO: изменение меж этажного расстояния
            floorPosition.push_back(tempRect);
            connect(btn, QOverload<bool>::of(&QPushButton::clicked),
                    [=] (bool checked) {setNextPosition(floorPosition[i]);});
//        }
        ui->verticalLayout_2->addWidget(btn);
    }
}

