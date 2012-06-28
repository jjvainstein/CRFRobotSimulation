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

    QFile logFile;
    QTextStream data;

    QFile testFile;
    QTextStream testData;

    QGraphicsScene scene;
    QHash<Robot*, QPair<RobotState*, QGraphicsEllipseItem*>* >  robots;    
    QList<Robot*> robotsAux;

    QList<Robot*> robotsPrev;

    Robot* seeker;
    QTimer saveState;
    int countOfRobots;
    int scenaryWidth;
    int scenaryHeight;

private:
    void addRobots();
    void addRobot(QString id, QString role, QPointF pos = QPointF(0, 0));    
    bool isOccupiedPosition(QPointF pos);
    QPointF getAvailablePosition();
    void checkTagAction();

protected slots:
    void destinationReached(Robot* r);
    void updateState(Robot* r, RobotState* rs);
    void saveCurrentState();

};

#endif // STAGE_H
