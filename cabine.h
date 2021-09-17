#ifndef CABINE_H
#define CABINE_H
#include <QObject>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>

class cabine : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QRectF geometry READ geometry WRITE setGeometry)
    Q_INTERFACES(QGraphicsItem)
public:
    explicit cabine(QObject *parent = nullptr);
    cabine(const QRectF &rect, QObject *parent = nullptr);

    QRectF geometry() const;
    void setGeometry(const QRectF &rect);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int cabineWidth = 10;
    int cabineHeight = 10;
    QRectF rectangle;

};

#endif // CABINE_H
