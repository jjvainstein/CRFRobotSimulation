#include "crftagrobot.h"
#include "ui_crftagrobot.h"

CRFTagRobot::CRFTagRobot(QWidget *parent) : QMainWindow(parent), ui(new Ui::CRFTagRobot){
    ui->setupUi(this);
}

void CRFTagRobot::drawPath(){

    //Flecha superior
    QVector<QPoint> arrow0;
    arrow0.append(QPoint(190, 10)); //punto sobre la recta
    arrow0.append(QPoint(200, 5));  //punto arriba de la recta
    arrow0.append(QPoint(200, 15)); //punto debajo de la recta
    //Flecha inferior
    QVector<QPoint> arrow1;
    arrow1.append(QPoint(190, 400)); //punto sobre la recta
    arrow1.append(QPoint(200, 395)); //punto arriba de la recta
    arrow1.append(QPoint(200, 405)); //punto debajo de la recta
    //Flecha diagonal 1
    QVector<QPoint> arrow2;
    arrow2.append(QPoint(170, 175)); //punto sobre de la recta
    arrow2.append(QPoint(170, 165)); //punto arriba de la recta
    arrow2.append(QPoint(160, 175)); //punto debajo de la recta
    //Flecha diagonal 2
    QVector<QPoint> arrow3;
    arrow3.append(QPoint(230, 175));
    arrow3.append(QPoint(220, 175));
    arrow3.append(QPoint(230, 185));

    this->scene.addPolygon(QPolygon(arrow0), QPen(), QBrush(QColor("black")));
    this->scene.addPolygon(QPolygon(arrow1), QPen(), QBrush(QColor("black")));
    this->scene.addPolygon(QPolygon(arrow2), QPen(), QBrush(QColor("black")));
    this->scene.addPolygon(QPolygon(arrow3), QPen(), QBrush(QColor("black")));
    this->scene.addLine(QLine(QPoint(0, 10), QPoint(400, 400)),QPen(QColor("black")));
    this->scene.addLine(QLine(QPoint(0, 400), QPoint(400, 10)),QPen(QColor("black")));
    this->scene.addLine(QLine(QPoint(0, 10), QPoint(400, 10)),QPen(QColor("black")));
    this->scene.addLine(QLine(QPoint(0, 400), QPoint(400, 400)),QPen(QColor("black")));
}

CRFTagRobot::~CRFTagRobot(){
    delete ui;
}
