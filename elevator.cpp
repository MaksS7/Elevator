#include "elevator.h"
#include "ui_elevator.h"
#include <QDebug>

Elevator::Elevator(QWidget *parent)
    : QMainWindow(parent)
    , duration(1000)
    , heightCabine(30)
    , widthCabine(30)
    , floorCount(5)
    , startPosition(30, 30, widthCabine, heightCabine)
    , currentPosition(startPosition)
    , cab(nullptr)
    , ui(new Ui::Elevator)
{
    ui->setupUi(this);
    ui->spinBoxFloorCount->setValue(5);
    //TODO: Добавить генерацию сцены от количесвта этажей
    //TODO: Добавить автоматическую генерацию кнопок по этажам
    //TODO: Добавить индикацию движения лифта
    //TODO: Добавить очередь запросов лифта

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
    connect(animation, &QPropertyAnimation::finished,
            [this] (){currentPosition = nextPosition;
                    scene->update();
                    emit arrivedOnTheFloor(floorPosition.indexOf(currentPosition)); //TODO: Открытие дверей по сигналу
    });

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
    int tempCurentfloor = floorPosition.indexOf(currentPosition);
    int tempNextFloor = floorPosition.indexOf(nextPosition);
    int tempDuration = duration * qAbs(tempNextFloor - tempCurentfloor);
    animation->setDuration(tempDuration);
//    animation->setStartValue(startPosition);
    animation->setEndValue(nextPosition);
    animation->start();
    emit theElevatorHasLeft(tempCurentfloor > tempNextFloor ? DOWN : UP); //TODO: выводить напревление движения
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
            tempRect.moveTop(heightCabine * (3 * (i)) + heightCabine); //TODO: изменение меж этажного расстояния
            floorPosition.push_back(tempRect);
            connect(btn, QOverload<bool>::of(&QPushButton::clicked),
                    [=] (bool checked) {setNextPosition(floorPosition[i]);});
//        }
        ui->verticalLayout_2->addWidget(btn);
    }
}

