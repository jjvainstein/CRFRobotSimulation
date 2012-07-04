#include "robot.h"

Robot::Robot(QString id, QString role, QPointF initPos) : QThread() {
    this->id = id;
    this->role = role;
    this->currentPosition = initPos;
    this->speed = 500;
}

void Robot::setRole(QString role){
    //this->speed = 10;
    this->role = role;
}

void Robot::setDestination(QPointF pos){
    this->destination = pos;
}

QString Robot::getId(){
    return this->id;
}

QString Robot::getRole(){
    return this->role;
}

QPointF Robot::getPosition(){
    return this->currentPosition;
}

QPointF Robot::getDestination(){
    return this->destination;
}

void Robot::run(){    
    this->timer.setInterval(this->speed);
    connect(&this->timer, SIGNAL(timeout()), this, SLOT(updatePosition()));

    this->accelerate.setInterval(500);
    connect(&this->accelerate, SIGNAL(timeout()), this, SLOT(updateSpeed()));

    this->waitForTag.setInterval(5000);
    this->waitForTag.setSingleShot(true);
    connect(&this->waitForTag, SIGNAL(timeout()), this, SLOT(resume()));
    this->recentlyTagged = false;

    this->timer.start();
    this->accelerate.start();
}

void Robot::updatePosition(){
    this->previousPosition = this->currentPosition;

    int xPos = this->currentPosition.x();
    int yPos = this->currentPosition.y();
    int xDest = this->destination.x();
    int yDest = this->destination.y();

    if (!this->recentlyTagged){
        this->currentPosition.setX(xPos + (xDest - xPos)/(abs(xPos - xDest) == 0 ? 1 : abs(xPos - xDest)));
        this->currentPosition.setY(yPos + (yDest - yPos)/(abs(yPos - yDest) == 0 ? 1 : abs(yPos - yDest)));
    }    

    emit sendState(this, new RobotState(this->currentPosition, sqrt(pow(this->previousPosition.x() - this->currentPosition.x(), 2) + pow(this->previousPosition.y() - this->currentPosition.y(), 2))/this->speed));
    //emit sendState(this, new RobotState(this->currentPosition, abs(this->previousPosition.x() - this->currentPosition.x()) + abs(this->previousPosition.y() - this->currentPosition.y())));

    if (this->currentPosition == this->destination){        
        emit arrived(this);
    }
}

void Robot::updateSpeed(){
    this->speed = (this->speed - 25 <= 17) ? 17 : this->speed - 25;
    this->timer.setInterval(this->speed);
    this->timer.start();
}

void Robot::setTagged(){
    this->recentlyTagged = true;
    this->role = "seeker";
    this->speed = 500;
    /*this->speed = 10;
    disconnect(&this->timer, SIGNAL(timeout()), this, SLOT(updatePosition()));
    disconnect(&this->accelerate, SIGNAL(timeout()), this, SLOT(updateSpeed()));
    this->timer.stop();
    this->accelerate.stop();*/
    this->waitForTag.start();
}

bool Robot::wasRecentlyTagged(){
    return this->recentlyTagged;
}

void Robot::resume(){
    this->recentlyTagged = false;
}
