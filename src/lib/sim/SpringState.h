#ifndef SPRINGSTATE_H
#define SPRINGSTATE_H

#include "sim/State.h"

class SpringState : public State
{
public:
    SpringState();

    enum    params {
        currentTime,
        positionX,
        velocityX,
        endParams
    };

};

#endif // SPRINGSTATE_H
