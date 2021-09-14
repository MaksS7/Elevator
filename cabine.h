#ifndef CABINE_H
#define CABINE_H
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>

class cabine : public QGraphicsItem
{
public:
     QRectF boundingRect() const override
     {
         return QRectF(0,0,100,100);
     }

     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget) override
     {
         painter->setBrush(QColor(Qt::black));
         painter->fillRect(0, 0, 100, 100, Qt::black);
         painter->drawRect(-100, -100, 100, 100);
     }

    cabine();
};

#endif // CABINE_H
