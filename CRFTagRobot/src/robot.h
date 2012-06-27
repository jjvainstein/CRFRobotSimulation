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
    QString getId();
    QString getRole();
    QPointF getPosition();
    QPointF getDestination();
    void setTagged();
    bool wasRecentlyTagged();

signals:
    void sendState(Robot* me, RobotState* currentState);
    void arrived(Robot* me);

private:

    QTimer timer;
    QTimer accelerate;
    QTimer waitForTag;
    QString id;
    QString role;
    QPointF previousPosition;
    QPointF currentPosition;
    QPointF destination;
    int speed;
    bool recentlyTagged;

    void run();

private slots:
    void updatePosition();
    void updateSpeed();
    void resume();
};

#endif // ROBOT_H
