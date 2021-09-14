#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QMainWindow>
#include <cabine.h>

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

private:
    Ui::Elevator *ui;
};
#endif // ELEVATOR_H
