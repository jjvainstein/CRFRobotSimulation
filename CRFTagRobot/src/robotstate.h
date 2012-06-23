#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H

#include <QtCore>
#include <QtGui>

class RobotState
{
public:
    RobotState(QPointF position, double velocity);
    ~RobotState(){}

    QPointF position;
    double  velocity;
    bool    velocityThreshold;
    double  chasing;
    double  distance;
    bool    distanceThreshold;
};

#endif // ROBOTSTATE_H
