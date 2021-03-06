#include "cabine.h"
#include <QPen>
#include <QDebug>

//TODO: добавить открытие дверей
//TODO: добавить сигнла об открытии
cabine::cabine(QObject *parent) :
    QObject(parent)
{
    rectangle = QRectF(10, 10, cabineWidth, cabineHeight);
}

cabine::cabine(const QRectF &rect, QObject *parent) :
    QObject(parent),
    rectangle(rect)
{
}

QRectF cabine::geometry() const
{
    return rectangle;
}

//TODO: вариация с rectangle.moveTo(QPoint)
void cabine::setGeometry(const QRectF &rect)
{
    if (rect != rectangle) {
        rectangle.moveTo(rect.x(), rect.y());
        update();
    }
}

QRectF cabine::boundingRect() const
{
    return rectangle;
}

void cabine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
//    QPen pen;
//    pen.setWidth(3);
//    painter->setPen(pen);
    painter->drawRect(rectangle);
}

