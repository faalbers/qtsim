#include "springs/Widget.h"
#include <QTimer>

Widget::Widget(int windowWidth, SpringSim::steptype stepType, QWidget *parent)
    : QWidget(parent),
      sim(0)
{
    // Draw setup
    circleRadius = 15;
    circleWidth = 3;
    int circleSize = circleRadius*2 + circleWidth*2;
    int windowHeight = circleSize + 20;
    worldSize = 2.0; //meters
    pixelsPerMeter = (float) (windowWidth - circleSize - 20)  / worldSize;
    originPixelsX = 0.5 * ( float ) windowWidth;
    originPixelsY = 0.5 * ( float ) windowHeight;

    // Setup widget
    setFixedSize(windowWidth, windowHeight);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::yellow);
    setAutoFillBackground(true);
    setPalette(Pal);

    // Draw tools
    circlePen = QPen(Qt::black);
    circlePen.setWidth(circleWidth);

    sim = new SpringSim(stepType);

}

Widget::~Widget()
{
    if (sim) delete sim;
}

void Widget::animate()
{
    float dt = 0.001 * qobject_cast<QTimer*>(sender())->interval();
    sim->stepTime(dt);
    repaint();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    float posX = (sim->currentX() * pixelsPerMeter) + originPixelsX;
    float posY = originPixelsY;
    painter.setPen(circlePen);
    painter.drawEllipse(QPoint((int) posX, (int) posY), circleRadius, circleRadius);

    painter.end();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        sim->init();
    }
}
