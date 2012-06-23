#include "stage.h"

Stage::Stage(QWidget *parent) : QGraphicsView(parent){

    // Create seed for the random
    // That is needed only once on application startup
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    this->scenaryWidth = 400;
    this->scenaryHeight = 400;
    this->scene.addRect(0, 0,this->scenaryWidth, this->scenaryHeight, QPen(QColor("black")));
    this->setScene(&this->scene);
    this->countOfRobots = 3;    
    addRobots();
}

void Stage::addRobots(){

    addRobot("0", "seeker", getAvailablePosition());

    for (int i = 1; i < this->countOfRobots; i++){
        addRobot(QString::number(i), "passive", getAvailablePosition());
    }

    foreach(Robot* r, robots.keys()){
       r->start();
    }
}

void Stage::addRobot(QString id, QString role, QPointF pos){
    qDebug() << "id: " << id << " -- POS: " << pos;
    Robot* r = new Robot(id, role, pos);
    RobotState* rs = new RobotState(pos, 0);
    QGraphicsEllipseItem* body = new QGraphicsEllipseItem(pos.x(), pos.y(), 10, 10, 0, &this->scene);

    if (role == "seeker")
         body->setBrush(QBrush(QColor("red")));
    else body->setBrush(QBrush(QColor("blue")));

    r->setDestination(getAvailablePosition());
    this->robots[r] = new QPair<RobotState*, QGraphicsEllipseItem*> (rs, body);

    connect(r, SIGNAL(arrived(Robot*)), this, SLOT(destinationReached(Robot*)));
    connect(r, SIGNAL(sendState(Robot*,RobotState*)), this, SLOT(updateState(Robot*, RobotState*)));
}

QPointF Stage::getAvailablePosition(){

    QPointF np = QPointF(qrand() % (this->scenaryWidth + 1), qrand() % (this->scenaryHeight + 1));

    while (isOccupiedPosition(np)){
        np = QPointF(qrand() % this->scenaryWidth, qrand() % this->scenaryHeight);
    }

    return np;
}

bool Stage::isOccupiedPosition(QPointF pos){
    foreach (Robot *r, this->robots.keys()){
        if (r->getPosition() == pos)
            return true;
    }

    return false;
}

void Stage::updateState(Robot* r, RobotState *rs){

    this->scene.removeItem(this->robots[r]->second);
    delete this->robots[r];

    QGraphicsEllipseItem* body = new QGraphicsEllipseItem(r->getPosition().x(), r->getPosition().y(), 10, 10, 0, &this->scene);

    if (r->getRole() == "seeker")
         body->setBrush(QBrush(QColor("red")));
    else body->setBrush(QBrush(QColor("blue")));

    this->robots[r] = new QPair<RobotState*, QGraphicsEllipseItem*> (rs, body);    
}

void Stage::destinationReached(Robot *r){
    r->setDestination(getAvailablePosition());
}
