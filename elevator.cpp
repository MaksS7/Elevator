#include "elevator.h"
#include "ui_elevator.h"


Elevator::Elevator(QWidget *parent)
    : QMainWindow(parent)
    , duration(1000)
    , heightCabine(30)
    , widthCabine(30)
    , floorCount(3)
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

    ui->graphicsView->setSceneRect(QRectF(0,0, 300, 300));
    scene = new QGraphicsScene(this);

    scene->addItem(cab);
    ui->graphicsView->setScene(scene);
    animation = new QPropertyAnimation(cab, "geometry");

    /***********************************************************************/
    connect(ui->btnStart, &QPushButton::clicked, this, &Elevator::startAnimation);
    connect(ui->btnReset, &QPushButton::clicked, this, &Elevator::resetPosition);
    connect(ui->spinBoxFloorCount, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &Elevator::setFloorCount);
    connect(animation, &QPropertyAnimation::finished, scene,
            [this] (){currentPosition = nextPosition;
                    scene->update();
                    emit arrivedOnTheFloor(floorPosition.indexOf(currentPosition)); //TODO: Открытие дверей по сигналу
    });
    /***********************************************************************/
    timer = new QTimer(this);

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
    animation->setStartValue(currentPosition);
    animation->setEndValue(nextPosition);
    animation->start();
    connect(animation, &QPropertyAnimation::stateChanged, this, &Elevator::update);
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

void Elevator::update()
{
    scene->update();
    ui->graphicsView->update();
}

void Elevator::addFloor(int count)
{
    if (!buttonVector.isEmpty()) {
        for (auto &item : buttonVector) {
            delete item;
        }
    }
    for (int i(count - 1); i >= 0 ; i--) {
        //Добавление координат этажа в массив, привязка координат к кнопке этого этажа.
        btn = new QPushButton(QString::number(i + 1));
        buttonVector.push_back(btn);
        QRectF tempRect = startPosition;
        tempRect.moveTop(heightCabine * (3 * (i)) + heightCabine); //TODO: изменение меж этажного расстояния
        floorPosition.push_back(tempRect);

        connect(btn, QOverload<bool>::of(&QPushButton::clicked),
                [=] (bool checked) {Q_UNUSED(checked) setNextPosition(floorPosition[i]);});
        ui->verticalLayout_2->addWidget(btn);
    }
}

