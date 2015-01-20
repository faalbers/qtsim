#include "sim/SpringSim.h"
#include <math.h>

SpringSim::SpringSim(int _stepType)
    : stepType(_stepType)
{
    stiffness = 5.0;
    mass = 0.5;
    accelConstant = stiffness / mass;
    accelConstantInv = -accelConstant;
    initPos = 0.65;
    initVel = 0;

    *initState.get(SpringState::currentTime) = 0.0;
    *initState.get(SpringState::positionX) = initPos;
    *initState.get(SpringState::velocityX) = initVel;

    // Copy initial state to current state
    state = initState;

}

void SpringSim::init()
{
    // Copy initial state to current state
    state = initState;
}

void SpringSim::stepTime(float &dt)
{
    switch(stepType)
    {
        case FUNCTION:
            stepFunction(dt);
            break;
        case EULER:
            stepEuler(dt);
            break;
        case EULERCROMER:
            stepEulerCromer(dt);
            break;
        case MIDPOINT:
            stepMidpoint(dt);
            break;
        case VERLET:
            stepVerlet(dt);
            break;
        case RUNGEKUTTA2:
            stepRungeKutta2(dt);
            break;
        case RUNGEKUTTA4:
            stepRungeKutta4(dt);
            break;
        default:
            return;
    }
}

void SpringSim::stepFunction(float &dt)
{
    float *currentTimeP = state.get(SpringState::currentTime);
    float *positionXP = state.get(SpringState::positionX);

    float km = sqrt(accelConstant);
    float kmt = km * *currentTimeP;
    *positionXP = initPos*cos(kmt)+(initVel/km)*sin(kmt);

    // Update current time.
    *currentTimeP += dt;
}

float SpringSim::accelFromPos(float *position)
{
    return accelConstantInv * *position;
}

void SpringSim::stepEuler(float &dt)
{
    float *currentTimeP = state.get(SpringState::currentTime);
    float *positionXP = state.get(SpringState::positionX);
    float *velocityXP = state.get(SpringState::velocityX);

    // Compute acceleration from current position.
    float A = accelFromPos(positionXP);

    // Update position based on current velocity.
    *positionXP += dt * *velocityXP;

    // Update velocity based on acceleration.
    *velocityXP += dt * A;

    // Update current time.
    *currentTimeP += dt;
}

void SpringSim::stepEulerCromer(float &dt)
{
    float *currentTimeP = state.get(SpringState::currentTime);
    float *positionXP = state.get(SpringState::positionX);
    float *velocityXP = state.get(SpringState::velocityX);

    // Compute acceleration from current position.
    float A = accelFromPos(positionXP);

    // Update velocity based on acceleration.
    *velocityXP += dt * A;

    // Update position based on current velocity.
    *positionXP += dt * *velocityXP;

    // Update current time.
    *currentTimeP += dt;
}

void SpringSim::stepMidpoint(float &dt)
{
    float *currentTimeP = state.get(SpringState::currentTime);
    float *positionXP = state.get(SpringState::positionX);
    float *velocityXP = state.get(SpringState::velocityX);
    float dtHalf = dt * 0.5;

    // Compute acceleration from current position.
    float A = accelFromPos(positionXP);

    // Update position half-way.
    *positionXP += dtHalf * *velocityXP;

    // Update velocity based on acceleration.
    *velocityXP += dt * A;

    // Update position half-way.
    *positionXP += dtHalf * *velocityXP;

    // Update current time.
    *currentTimeP += dt;
}


void SpringSim::stepVerlet(float &dt)
{
    float *currentTimeP = state.get(SpringState::currentTime);
    float *positionXP = state.get(SpringState::positionX);
    float *velocityXP = state.get(SpringState::velocityX);
    float dtHalf = dt * 0.5;

    // Compute acceleration from current position.
    float A = accelFromPos(positionXP);

    // Update velocity based on acceleration half-way.
    *velocityXP += dtHalf * A;

    // Update position.
    *positionXP += dt * *velocityXP;

    // Re compute acceleration from current position.
    A = accelFromPos(positionXP);

    // Update velocity based on acceleration half-way.
    *velocityXP += dtHalf * A;

    // Update current time.
    *currentTimeP += dt;

}

void SpringSim::stepRungeKutta2(float &dt)
{
    float *currentTimeP = state.get(SpringState::currentTime);
    float *positionXP = state.get(SpringState::positionX);
    float *velocityXP = state.get(SpringState::velocityX);
    float dtHalf = dt * 0.5;

    float vStar1 = *velocityXP;
    float aStar1 = accelFromPos(positionXP);

    float vStar2 = *velocityXP + (dt * aStar1);
    float xTmp2   = *positionXP + (dt * vStar1);
    float aStar2 = accelFromPos(&xTmp2);

    *positionXP += dtHalf * (vStar1 + vStar2);
    *velocityXP += dtHalf * (aStar1 + aStar2);

    // Update current time.
    *currentTimeP += dt;

}

void SpringSim::stepRungeKutta4(float &dt)
{
    float *currentTimeP = state.get(SpringState::currentTime);
    float *positionXP = state.get(SpringState::positionX);
    float *velocityXP = state.get(SpringState::velocityX);
    float dtHalf = dt * 0.5;

    float vStar1 = *velocityXP;
    float aStar1 = accelFromPos(positionXP);

    float vStar2 = *velocityXP + (dtHalf * aStar1);
    float xTmp2   = *positionXP + (dtHalf * vStar1);
    float aStar2 = accelFromPos(&xTmp2);

    float vStar3 = *velocityXP + (dtHalf * aStar2);
    float xTmp3  = *positionXP + (dtHalf * vStar2);
    float aStar3 = accelFromPos(&xTmp3);

    float vStar4 = *velocityXP + (dt * aStar3);
    float xTmp4  = *positionXP + (dt * vStar3);
    float aStar4 = accelFromPos(&xTmp4);

    *positionXP += (dt / 6.0) *
                        (vStar1 + (2.0*vStar2) + (2.0*vStar3) + vStar4);
    *velocityXP += (dt / 6.0) *
                        (aStar1 + (2.0*aStar2) + (2.0*aStar3) + aStar4);

    // Update current time.
    *currentTimeP += dt;

}


float SpringSim::currentX()
{
    return *state.get(SpringState::positionX);
}

