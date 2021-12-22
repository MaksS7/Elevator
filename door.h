#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>

class door : public QObject, public QGraphicsItem
{
    Q_OBJECT
//    Q_PROPERTY(QRectF geometry READ geometry WRITE setGeometry)
//    Q_INTERFACES(QGraphicsItem)
public:
    explicit door(QObject *parent = nullptr);
    explicit door(const QRectF &rect, int number, QObject *parent = nullptr);

    QRectF geometry() const;
    void setGeometry(const QRectF &rect);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void openTheDoor(int number);


private:
    int doorLeftWidth;
    int doorRightWidth;
    int doorHeight;
    int floorNumber;
    QRectF rectangle;
    QRectF openedPosition;
    QRectF closedPosition;

signals:
    void doorIsClose();
    void doorIsOpen();
};

#endif // DOOR_H
