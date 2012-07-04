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

    this->testing = true;

    if (testing){
         this->logFile.setFileName("test-7.txt");
         this->file2.setFileName("test2-7.txt");
         this->file3.setFileName("test3-7.txt");
         this->file4.setFileName("test4-7.txt");
    }
    else {
        this->logFile.setFileName("train.txt");
        this->file2.setFileName("train2.txt");
        this->file3.setFileName("train3.txt");
        this->file4.setFileName("train4.txt");
    }

    if (!this->logFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    this->data.setDevice(&this->logFile);

    if (!this->file2.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    this->streamFile2.setDevice(&this->file2);


    if (!this->file3.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    this->streamFile3.setDevice(&this->file3);

    if (!this->file4.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    this->streamFile4.setDevice(&this->file4);


    this->saveState.setInterval(17);
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

    //PreviousState
    //this->previousState[r] = new RobotState(pos, 0);
    this->previousStates[r] = new QList<RobotState*>();
    this->previousStates[r]->append(new RobotState(pos, 0));//t_2
    this->previousStates[r]->append(new RobotState(pos, 0));//t_1



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

    /*delete this->previousState[r];
    delete this->robots[r]->second;
    this->previousState[r] = this->robots[r]->first;
    delete this->robots[r];*/

    delete this->previousStates[r]->at(0);
    this->previousStates[r]->removeAt(0); //borro state del tiempo t-2
    delete this->robots[r]->second; //boroo el state inmediato actual (antes de actualizar)
    this->previousStates[r]->append(this->robots[r]->first); //guardo el puntero para que se convierta en el estado en t-1
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
    QString item = "";
    QString item2 = "";
    QString item3 = "";
    QString item4 = "";

    RobotState* cs;//current state
    //RobotState* ps;//previous state
    RobotState* pst_1;//previous state t-1
    RobotState* pst_2;//previous state t-2

    //Para el calculo del atributo chasing
    /*Robot* cn; //Closest Neighbor
    QPointF rv; //Resta Vectores
    QPointF rv2; //Resta Vectores
    double aux; //Para las divisiones*/

    //Para el calculo del atributo distance threshold
    int countRobot = 1;
    double distanceThreshold = 25;
    double distanceThreshold2 = 50;
    QString attrDist = "";
    QString attrDist1;
    QString attrDist2;
    QString attrDist_2 = "";
    QString attrDist1_2;
    QString attrDist2_2;

    //QString v;

    item = "r" + this->seeker->getId();
    item2 = "r" + this->seeker->getId();
    item3 = "r" + this->seeker->getId();
    item4 = "r" + this->seeker->getId();

    foreach (Robot* r, this->robotsAux){
        //ps = this->previousState[r];
        cs = this->robots[r]->first;

        pst_2 = this->previousStates[r]->at(0);
        pst_1 = this->previousStates[r]->at(1);

        //v = (r->getId() == this->seeker->getId()) ? "1" : "0";

        /*---------------NO ANDUVO COMO LA GENTE!!!!------------------------*/
                        /*[Training]Los datos contienen la posición anterior, la actual, la velocidad anterior y la velocidad actual*/
                        /*
                        info = info + "\t" + "pos[0]=(" + QString::number(this->robots[r]->first->getPosition().x()) +  "," + QString::number(this->robots[r]->first->getPosition().y()) + ")" +
                                      "\t" + "pos[-1]=(" + QString::number(this->previousState[r]->getPosition().x()) +  "," + QString::number(this->previousState[r]->getPosition().y()) + ")" +
                                      "\t" + "speed[0]=" + QString::number(this->robots[r]->first->getSpeed()) + "\t" + "speed[-1]=" + QString::number(this->previousState[r]->getSpeed());
                       */

                        /*[Training]Los datos contienen la posición anterior, la actual, la velocidad anterior,la velocidad actual,
                                    threshold anterior y actual, y un atributo stopping
                        */
                        /*
                        item = item + "\t" + "pos[-1]=(" + QString::number(ps->getPosition().x()) +  "," + QString::number(ps->getPosition().y()) + ")" + "\t" + "pos[0]=(" + QString::number(cs->getPosition().x()) +  "," + QString::number(cs->getPosition().y()) + ")" +
                                      "\t" + "speed[-1]=" + QString::number(ps->getSpeed()) + "\t" + "speed[0]=" + QString::number(cs->getSpeed()) + "\t" + "threshold[-1]=" + QString::number(ps->getSpeed() < 0.020) + "\t" + "threshold[0]=" + QString::number(cs->getSpeed() < 0.020) + "\t" + "stopping=" + QString::number((cs->getSpeed() - ps->getSpeed()<=0));
                        */

                        /*
                        item = item + this->seeker->getId() + "\t" + "pos[-1]=(" + QString::number(ps->getPosition().x()) +  "," + QString::number(ps->getPosition().y()) + ")" + "\t" + "pos[0]=(" + QString::number(cs->getPosition().x()) +  "," + QString::number(cs->getPosition().y()) + ")" +
                                      "\t" + "speed[-1]=" + QString::number(ps->getSpeed()) + "\t" + "speed[0]=" + QString::number(cs->getSpeed()) + "\t" + "threshold[-1]=" + QString::number(ps->getSpeed() < 0.020) + "\t" + "threshold[0]=" + QString::number(cs->getSpeed() < 0.020) + "\t" + "stopping=" + QString::number((cs->getSpeed() - ps->getSpeed()<=0)) + "\n";

                        item2 = item2 + this->seeker->getId() + "\t" + "speed[-1]=" + QString::number(ps->getSpeed()) + "\t" + "speed[0]=" + QString::number(cs->getSpeed()) + "\t" + "threshold[-1]=" + QString::number(ps->getSpeed() < 0.020) + "\t" + "threshold[0]=" + QString::number(cs->getSpeed() < 0.020) + "\t" + "stopping=" + QString::number((cs->getSpeed() - ps->getSpeed()<=0)) + "\n";
                        */
        /*-------------------------------------------------------------------*/

        /* SeekerID r0_pos=[x,y] r0_speedThreshold= r0_stopping= r1_pos.......*/
            /*    item = item + "\t" + "r" + r->getId() + "_pos=[" + QString::number(cs->getPosition().x()) +  "," + QString::number(cs->getPosition().y()) + "]:" + v +
                              "\t" + "r" + r->getId() + "_speedTheshold=" + QString::number(cs->getSpeed() < 0.020) + ":" + v + "\t" + "r" + r->getId() + "_stopping=" + QString::number((cs->getSpeed() - ps->getSpeed() < 0)) + ":" + v;
            */

        /* SeekerID r0_pos=[x,y] r0_speedThreshold= r0_stopping= r1_pos....... Dejando un espacio entre cada tiempo t*/
            /*  item2 = item2 + "\t" + "r" + r->getId() + "_pos=[" + QString::number(cs->getPosition().x()) +  "," + QString::number(cs->getPosition().y()) + "]" +
                          "\t" + "r" + r->getId() + "_speedTheshold=" + QString::number(cs->getSpeed() < 0.020) + "\t" + "r" + r->getId() + "_stopping=" + QString::number((cs->getSpeed() - ps->getSpeed() < 0));
            */

        /* chasing*/
        /*cn = closestNeighbor(r);
        rv = restaVectores(cn->getPosition(), cs->getPosition());
        aux = 1 / modulo(rv);
        rv.setX(rv.x() * aux);
        rv.setY(rv.y() * aux);
        aux = 1 / cs->getSpeed();
        rv.setX(rv.x() * aux);
        rv.setY(rv.y() * aux);*/

        attrDist1 = ((distance(cs->getPosition(), this->robots[this->robotsAux[countRobot % this->countOfRobots]]->first->getPosition()) <= distanceThreshold ||
                distance(pst_1->getPosition(), this->previousStates[this->robotsAux[countRobot % this->countOfRobots]]->at(1)->getPosition()) <= distanceThreshold) &&
                distance(pst_2->getPosition(), this->previousStates[this->robotsAux[countRobot % this->countOfRobots]]->at(0)->getPosition()) <= distanceThreshold) ? "1" : "0";

        attrDist = attrDist + "\t" + "dist1(r" + r->getId() + ",r" + this->robotsAux[countRobot % this->countOfRobots]->getId() + ")= " + attrDist1;

        attrDist2 = (distance(cs->getPosition(), this->robots[this->robotsAux[countRobot % this->countOfRobots]]->first->getPosition()) > distanceThreshold &&
                     distance(pst_1->getPosition(), this->previousStates[this->robotsAux[countRobot % this->countOfRobots]]->at(1)->getPosition()) > distanceThreshold) ? "1" : "0";

        attrDist = attrDist + "\t" + "dist2(r" + r->getId() + ",r" + this->robotsAux[countRobot % this->countOfRobots]->getId() + ")= " + attrDist2;


        attrDist1_2 = ((distance(cs->getPosition(), this->robots[this->robotsAux[countRobot % this->countOfRobots]]->first->getPosition()) <= distanceThreshold2 ||
                distance(pst_1->getPosition(), this->previousStates[this->robotsAux[countRobot % this->countOfRobots]]->at(1)->getPosition()) <= distanceThreshold2) &&
                distance(pst_2->getPosition(), this->previousStates[this->robotsAux[countRobot % this->countOfRobots]]->at(0)->getPosition()) <= distanceThreshold2) ? "1" : "0";

        attrDist_2 = attrDist_2 + "\t" + "dist1(r" + r->getId() + ",r" + this->robotsAux[countRobot % this->countOfRobots]->getId() + ")= " + attrDist1;

        attrDist2_2 = (distance(cs->getPosition(), this->robots[this->robotsAux[countRobot % this->countOfRobots]]->first->getPosition()) > distanceThreshold2 &&
                     distance(pst_1->getPosition(), this->previousStates[this->robotsAux[countRobot % this->countOfRobots]]->at(1)->getPosition()) > distanceThreshold2) ? "1" : "0";

        attrDist_2 = attrDist_2 + "\t" + "dist2(r" + r->getId() + ",r" + this->robotsAux[countRobot % this->countOfRobots]->getId() + ")= " + attrDist2;


        countRobot++;



        item = item + "\t" + "r" + r->getId() + "_pos=[" + QString::number(cs->getPosition().x()) +  "," + QString::number(cs->getPosition().y()) + "]" +
                      "\t" + "r" + r->getId() + "_speedTheshold=" + QString::number(cs->getSpeed() < 0.020) + "\t" + "r" + r->getId() + "_stopping=" + QString::number((cs->getSpeed() - pst_1->getSpeed() < 0));


        //item2 = item2 + "\t" + "r" + r->getId() + "_pos=[" + QString::number(cs->getPosition().x()) +  "," + QString::number(cs->getPosition().y()) + "]" +
         //               "\t" + "r" + r->getId() + "_speedTheshold=" + QString::number(cs->getSpeed() < 0.020) + "\t" + "r" + r->getId() + "_stopping=" + QString::number((cs->getSpeed() - pst_1->getSpeed() < 0));
    }




    //item = item + attrDist + "\n";
    //this->data << item;
    this->data << item + attrDist + "\n";

    this->streamFile2 << item + attrDist_2 + "\n";

    this->streamFile3 << item + attrDist + "\n\n";
    this->streamFile4 << item + attrDist_2 + "\n\n";
}

QPointF Stage::restaVectores(QPointF v1, QPointF v2){
    return QPointF(v1.x() - v2.x(), v1.y() - v2.y());
}

double Stage::modulo(QPointF v){
    sqrt(pow(v.x(), 2) + pow(v.y(), 2));
}

double Stage::distance(QPointF v1, QPointF v2){
    return sqrt(pow(v1.x() - v2.x(), 2) + pow(v1.y() - v2.y(), 2));
}
