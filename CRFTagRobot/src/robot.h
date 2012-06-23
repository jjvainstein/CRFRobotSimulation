#ifndef ROBOT_H
#define ROBOT_H

#include <QtCore>
#include <QtGui>
#include <math.h>
#include <robotstate.h>

class Robot : public QThread
{
    Q_OBJECT

public:

    Robot(QString id, QString role, QPointF initPos);

    //set
    void setRole(QString role);
    void setDestination(QPointF pos);

    //get
    QString getRole();
    QPointF getPosition();
    QPointF getDestination();

signals:
    void sendState(Robot* me, RobotState* currentState);
    void arrived(Robot* me);

private:

    QTimer timer;
    QString id;
    QString role;
    QPointF previousPosition;
    QPointF currentPosition;
    QPointF destination;    

    void run();

private slots:
    void updatePosition();
};

#endif // ROBOT_H
