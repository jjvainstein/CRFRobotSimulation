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

    QFile file2;
    QTextStream streamFile2;

    QFile file3;
    QTextStream streamFile3;

    QFile file4;
    QTextStream streamFile4;


    QGraphicsScene scene;
    QHash<Robot*, QPair<RobotState*, QGraphicsEllipseItem*>* >  robots;    
    QList<Robot*> robotsAux;

    //QHash<Robot*, RobotState*> previousState;
    QHash<Robot*, QList<RobotState*>* > previousStates;

    Robot* seeker;
    QTimer saveState;
    int countOfRobots;
    int scenaryWidth;
    int scenaryHeight;
    bool testing;

private:
    void addRobots();
    void addRobot(QString id, QString role, QPointF pos = QPointF(0, 0));    
    bool isOccupiedPosition(QPointF pos);
    QPointF getAvailablePosition();
    void checkTagAction();
    QPointF restaVectores(QPointF v1, QPointF v2);
    double modulo(QPointF v);
    Robot* closestNeighbor(Robot* r);
    double distance(QPointF v1, QPointF v2);

protected slots:
    void destinationReached(Robot* r);
    void updateState(Robot* r, RobotState* rs);
    void saveCurrentState();

};

#endif // STAGE_H
