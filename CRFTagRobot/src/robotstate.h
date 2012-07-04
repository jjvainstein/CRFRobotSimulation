#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H

#include <QtCore>
#include <QtGui>

class RobotState
{
public:
    RobotState(QPointF position, double speed);
    ~RobotState(){}

    QPointF position;
    double  speed;

    QPointF getPosition();
    double  getSpeed();
};

#endif // ROBOTSTATE_H
