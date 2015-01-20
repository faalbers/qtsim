#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sim/SpringSim.h"
#include "springs/Widget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    SpringSim   *simFunc;
    SpringSim   *simEuler;
    SpringSim   *simEulerCromer;
    Widget      *openGL;
};

#endif // MAINWINDOW_H
