#ifndef STAGE_H
#define STAGE_H

#include <QtCore>
#include <QtGui>
#include <robot.h>
#include <robotstate.h>

class Stage : public QGraphicsView
{
    Q_OBJECT

public:
    Stage(QWidget* parent);
    ~Stage(){}

    QFile log;
    QGraphicsScene scene;
    QHash<Robot*, QPair<RobotState*, QGraphicsEllipseItem*>* >  robots;    
    int countOfRobots;
    int scenaryWidth;
    int scenaryHeight;

private:
    void addRobots();
    void addRobot(QString id, QString role, QPointF pos = QPointF(0, 0));    
    void saveCurrentState();
    bool isOccupiedPosition(QPointF pos);
    QPointF getAvailablePosition();

protected slots:
    void destinationReached(Robot* r);
    void updateState(Robot* r, RobotState* rs);

};

#endif // STAGE_H
