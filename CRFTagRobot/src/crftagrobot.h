#ifndef CRFTAGROBOT_H
#define CRFTAGROBOT_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <src/robot.h>


namespace Ui {
    class CRFTagRobot;
}

class CRFTagRobot : public QMainWindow
{
    Q_OBJECT

public:
    explicit CRFTagRobot(QWidget *parent = 0);
    ~CRFTagRobot();

private:
    Ui::CRFTagRobot *ui;

    QGraphicsScene scene;

    void drawPath();
    void addRobot(bool tagger, QPoint pos);
};

#endif // CRFTAGROBOT_H
