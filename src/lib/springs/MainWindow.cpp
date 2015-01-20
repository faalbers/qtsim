#include "springs/MainWindow.h"
#include "springs/ui_MainWindow.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("Spring Methods"));
    setFixedWidth(520);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    QLabel *labelFunc  = new QLabel("Spring Function", this);
    Widget *widgetFunc = new Widget(500, SpringSim::FUNCTION, this);
    QLabel *labelEuler  = new QLabel("Euler Method", this);
    Widget *widgetEuler = new Widget(500, SpringSim::EULER, this);
    QLabel *labelEulerCromer  = new QLabel("Euler Cromer Method", this);
    Widget *widgetEulerCromer = new Widget(500, SpringSim::EULERCROMER, this);
    QLabel *labelMidpoint  = new QLabel("Midpoint Method", this);
    Widget *widgetMidpoint = new Widget(500, SpringSim::MIDPOINT, this);
    QLabel *labelVerlet  = new QLabel("Verlet Method", this);
    Widget *widgetVerlet = new Widget(500, SpringSim::VERLET, this);
    QLabel *labelRungeKutta2  = new QLabel("RungeKutta 2 Method", this);
    Widget *widgetRungeKutta2 = new Widget(500, SpringSim::RUNGEKUTTA2, this);
    QLabel *labelRungeKutta4  = new QLabel("RungeKutta 4 Method", this);
    Widget *widgetRungeKutta4 = new Widget(500, SpringSim::RUNGEKUTTA4, this);
    vlayout->addWidget(labelFunc);
    vlayout->addWidget(widgetFunc);
    vlayout->addWidget(labelEuler);
    vlayout->addWidget(widgetEuler);
    vlayout->addWidget(labelEulerCromer);
    vlayout->addWidget(widgetEulerCromer);
    vlayout->addWidget(labelMidpoint);
    vlayout->addWidget(widgetMidpoint);
    vlayout->addWidget(labelVerlet);
    vlayout->addWidget(widgetVerlet);
    vlayout->addWidget(labelRungeKutta2);
    vlayout->addWidget(widgetRungeKutta2);
    vlayout->addWidget(labelRungeKutta4);
    vlayout->addWidget(widgetRungeKutta4);
    vlayout->addStretch();
    centralWidget->setLayout(vlayout);
    setCentralWidget(centralWidget);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), widgetFunc, SLOT(animate()));
    connect(timer, SIGNAL(timeout()), widgetEuler, SLOT(animate()));
    connect(timer, SIGNAL(timeout()), widgetEulerCromer, SLOT(animate()));
    connect(timer, SIGNAL(timeout()), widgetMidpoint, SLOT(animate()));
    connect(timer, SIGNAL(timeout()), widgetVerlet, SLOT(animate()));
    connect(timer, SIGNAL(timeout()), widgetRungeKutta2, SLOT(animate()));
    connect(timer, SIGNAL(timeout()), widgetRungeKutta4, SLOT(animate()));
    timer->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}
