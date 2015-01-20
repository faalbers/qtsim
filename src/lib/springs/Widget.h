#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "sim/SpringSim.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(int windowWidth, SpringSim::steptype stepType, QWidget *parent = 0);
    ~Widget();

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    SpringSim           *sim;
    float               worldSize;
    float               pixelsPerMeter;
    float               originPixelsX;
    float               originPixelsY;
    QPen                circlePen;
    int                 circleRadius;
    int                 circleWidth;

};

#endif // WIDGET_H
