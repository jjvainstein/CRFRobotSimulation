#include "robotstate.h"


RobotState::RobotState(QPointF position, double speed){

    this->position = position;
    this->speed = speed;
}

QPointF RobotState::getPosition(){
    return this->position;
}

double RobotState::getSpeed(){
    return this->speed;
}
