#include "stage.h"

Stage::Stage(QWidget *parent) : QGraphicsView(parent){

    // Create seed for the random
    // That is needed only once on application startup
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    this->scenaryWidth = 610;
    this->scenaryHeight = 610;
    this->scene.addRect(0, 0,this->scenaryWidth, this->scenaryHeight, QPen(QColor("black")));
    this->setScene(&this->scene);

    this->logFile.setFileName("data.txt");
    if (!this->logFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    this->data.setDevice(&this->logFile);

    this->saveState.setInterval(100);
    connect(&this->saveState, SIGNAL(timeout()), this, SLOT(saveCurrentState()));

    this->countOfRobots = 3;
    addRobots();
    this->saveState.start();
}

//Método que crea y agrega los robots al escenario.
void Stage::addRobots(){

    for (int i = 0; i < this->countOfRobots - 1; i++){
        addRobot(QString::number(i), "passive", getAvailablePosition());        
    }

    addRobot("2", "seeker", getAvailablePosition());

    foreach(Robot* r, robots.keys()){
       r->start();
    }
}

//Método que crea y agrega al escenario un nuevo robot.
void Stage::addRobot(QString id, QString role, QPointF pos){

    Robot* r = new Robot(id, role, pos);
    RobotState* rs = new RobotState(pos, 0);
    QGraphicsEllipseItem* body = new QGraphicsEllipseItem(pos.x(), pos.y(), 20, 20, 0, &this->scene);

    if (role == "seeker"){
        this->seeker = r;
        body->setBrush(QBrush(QColor("red")));
    }
    else body->setBrush(QBrush(QColor("blue")));

    r->setDestination(getAvailablePosition());
    this->robots[r] = new QPair<RobotState*, QGraphicsEllipseItem*> (rs, body);

    connect(r, SIGNAL(arrived(Robot*)), this, SLOT(destinationReached(Robot*)));
    connect(r, SIGNAL(sendState(Robot*,RobotState*)), this, SLOT(updateState(Robot*, RobotState*)));

    this->robotsAux.append(r);
}

//Método que retorna una posición desocupada dentro del escenario.
QPointF Stage::getAvailablePosition(){

    QPointF np = QPointF(qrand() % (this->scenaryWidth - 9), qrand() % (this->scenaryHeight - 9));

    while (isOccupiedPosition(np)){
        np = QPointF(qrand() % (this->scenaryWidth - 9), qrand() % (this->scenaryHeight - 9));
    }

    return np;
}

//Método que retorna true si una dada posición ya esta siendo ocupada por otro robot.
bool Stage::isOccupiedPosition(QPointF pos){
    foreach (Robot *r, this->robots.keys()){
        if ((r->getPosition() == pos) || (r->getRole() == "seeker" && abs(r->getPosition().x() - pos.x()) <= 100 && abs(r->getPosition().y() - pos.y()) <= 100))
            return true;
    }

    return false;
}

//Se actualiza el estado de un determinado robot.
void Stage::updateState(Robot* r, RobotState *rs){

    this->scene.removeItem(this->robots[r]->second);
    delete this->robots[r]->first;
    delete this->robots[r]->second;
    delete this->robots[r];

    checkTagAction();

    QGraphicsEllipseItem* body = new QGraphicsEllipseItem(r->getPosition().x(), r->getPosition().y(), 20, 20, 0, &this->scene);

    if (r->getRole() == "seeker"){
        this->seeker = r;
        body->setBrush(QBrush(QColor("red")));
    }
    else body->setBrush(QBrush(QColor("blue")));

    this->robots[r] = new QPair<RobotState*, QGraphicsEllipseItem*> (rs, body);    
}

//Cuando un robot alcanza su destino se le asigna uno nuevo.
void Stage::destinationReached(Robot *r){
    if (r == this->seeker){
        int min = INT_MAX;
        QPointF dest;
        foreach(Robot*r, robots.keys()){
            if (r->getRole() != "seeker"){
                if ((abs(r->getPosition().x() - this->seeker->getPosition().x()) +  abs(r->getPosition().y() - this->seeker->getPosition().y())) < min){
                    min = (abs(r->getPosition().x() - this->seeker->getPosition().x()) +  abs(r->getPosition().y() - this->seeker->getPosition().y()));
                    dest = r->getPosition();
                }
            }
        }
        this->seeker->setDestination(dest);
    }
    else r->setDestination(getAvailablePosition());
}

void Stage::checkTagAction(){        
    foreach (Robot* r, this->robots.keys()){
        if (r->getRole() != "seeker"){
            if (!this->seeker->wasRecentlyTagged() && abs(this->seeker->getPosition().x() - r->getPosition().x()) <= 25 && abs(this->seeker->getPosition().y() - r->getPosition().y()) <= 25){
                r->setTagged();
                this->seeker->setRole("passive");
                this->seeker = r;
            }
        }
    }
}

void Stage::saveCurrentState(){
    QString info = "";

    info = this->seeker->getId();

    //foreach (Robot* r, this->robots.keys()){
    foreach (Robot* r, this->robotsAux){
        info = info + "\t" + "[" + QString::number(this->robots[r]->first->getPosition().x()) +  "," + QString::number(this->robots[r]->first->getPosition().y()) + "]" + "\t" + QString::number(robots[r]->first->getSpeed());
    }

    //info = info + this->seeker->getId() + "\n";
    info = info + "\n";
    this->data << info;
}
