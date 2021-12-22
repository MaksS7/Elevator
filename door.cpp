#include "door.h"
#include <QDebug>

door::door(QObject *parent) : QObject(parent)
{
    rectangle = QRectF(10,10, 10, 10);
}

door::door(const QRectF &rect, int number, QObject *parent):
    QObject(parent),
    floorNumber(number),
    rectangle(rect)
{
}

QRectF door::geometry() const
{
    return rectangle;
}

void door::setGeometry(const QRectF &rect)
{
    if (rect != rectangle) {
        rectangle = rect;
    }
}

QRectF door::boundingRect() const
{
    return rectangle;
}

void door::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->drawRect(rectangle.x() + 40, rectangle.y(),
                      rectangle.width() / 2, rectangle.height());
    painter->drawRect(rectangle.x()+ 40  + rectangle.width() / 2, rectangle.y(),
                      rectangle.width() / 2, rectangle.height());
}

void door::openTheDoor(int number)
{
    qDebug() << number;
}
