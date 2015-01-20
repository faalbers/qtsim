#ifndef SPRINGSIM_H
#define SPRINGSIM_H

#include "sim/SpringState.h"
#include <QPainter>
#include <QPaintEvent>

class SpringSim
{
public:
    SpringSim(int _stepType);

    enum    steptype {
        FUNCTION,
        EULER,
        EULERCROMER,
        MIDPOINT,
        VERLET,
        RUNGEKUTTA2,
        RUNGEKUTTA4
    };

    void init();
    float currentX();

    void stepTime(float &dt);

private:
    int         stepType;
    float       stiffness;
    float       mass;
    float       accelConstant;
    float       accelConstantInv;
    float       initPos;
    float       initVel;
    SpringState state;
    SpringState initState;

    float   accelFromPos(float *position);
    void    stepFunction(float &dt);
    void    stepEuler(float &dt);
    void    stepEulerCromer(float &dt);
    void    stepMidpoint(float &dt);
    void    stepVerlet(float &dt);
    void    stepRungeKutta2(float &dt);
    void    stepRungeKutta4(float &dt);

};

#endif // SPRINGSIM_H
