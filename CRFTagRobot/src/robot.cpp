#include "robot.h"

Robot::Robot(QString id, QString role, QPointF initPos) : QThread() {
    this->id = id;
    this->role = role;
    this->currentPosition = initPos;
}

void Robot::setRole(QString role){
    this->role = role;
}

void Robot::setDestination(QPointF pos){
    qDebug() << "NEW DESTINATION: " << pos;
    this->destination = pos;
}

QString Robot::getRole(){
    return this->role;
}

QPointF Robot::getPosition(){
    //qDebug() << "POS: " << this->currentPosition;
    return this->currentPosition;
}

QPointF Robot::getDestination(){
    return this->destination;
}

void Robot::run(){
    this->timer.setInterval(10);
    connect(&this->timer, SIGNAL(timeout()), this, SLOT(updatePosition()));
    this->timer.start();
}

void Robot::updatePosition(){
    this->previousPosition = this->currentPosition;

    int xPos = this->currentPosition.x();
    int yPos = this->currentPosition.y();
    int xDest = this->destination.x();
    int yDest = this->destination.y();

    this->currentPosition.setX(xPos + (xDest - xPos)/(abs(xPos - xDest) == 0 ? 1 : abs(xPos - xDest)));
    this->currentPosition.setY(yPos + (yDest - yPos)/(abs(yPos - yDest) == 0 ? 1 : abs(yPos - yDest)));

    //qDebug() << "id: " << this->id << " -- POS: " << this->currentPosition;

    emit sendState(this, new RobotState(this->currentPosition, sqrt(pow(this->previousPosition.x() - this->currentPosition.x(), 2) + pow(this->previousPosition.y() - this->currentPosition.y(), 2))));

    if (this->currentPosition == this->destination){
        qDebug() << "The robot reached the destination";
        //disconnect(&this->timer, SIGNAL(timeout()), this, SLOT(updatePosition()));
        emit arrived(this);
    }
}
