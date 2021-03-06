#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QMainWindow>
#include <cabine.h>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPropertyAnimation>
#include <QVector>
#include <QPushButton>
#include <door.h>
#include <QDebug>
#include <QTimer>
#include <QGraphicsItemGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class Elevator; }
QT_END_NAMESPACE

class Elevator : public QMainWindow
{
    Q_OBJECT

public:
    Elevator(QWidget *parent = nullptr);
    ~Elevator();
    QGraphicsScene *scene;
    QPropertyAnimation *animation;

    void startAnimation();
    void resetPosition();
    void setNextPosition(const QRectF &position);
    void setFloorCount(int8_t count);
    int8_t getFloorCount() const;

    enum directionElevator {
        DOWN,
        UP
    };
    Q_ENUM(directionElevator)

private slots:
    void update();

signals:
    void arrivedOnTheFloor(int floor);
    void theElevatorHasLeft(bool direction);

private:
    QVector<QPushButton*> buttonVector;
    QVector<QRectF> floorPosition;
    int duration;
    int heightCabine;
    int widthCabine;
    int8_t floorCount;
    QPushButton *btn;
    const QRectF startPosition;
    QRectF currentPosition;
    QRectF nextPosition;
    cabine *cab;
    door *doorOnTheFloor;
    QVector<door*> doorOnTheFloorVectro;
    QTimer *timer;

    void addFloor(int count);

    Ui::Elevator *ui;
};
#endif // ELEVATOR_H
