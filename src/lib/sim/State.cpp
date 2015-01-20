#include "sim/State.h"
#include <math.h>

State::State(int _dimSize, int _dim, int _paramsCount)
    :   state(0),
        dimSize(_dimSize),
        dim(_dim),
        size(pow(dimSize,dim)),
        paramsCount(_paramsCount)
{
    int fullSize = size * paramsCount;
    state = new float[fullSize];
}

State::State(const State& other )
    :   state(0),
        dimSize(other.dimSize),
        dim(other.dim),
        size(other.size),
        paramsCount(other.paramsCount)
{
    int fullSize = size * paramsCount;
    state = new float[fullSize];
    for ( int x = 0; x < fullSize; x++)
        state[x] = other.state[x];
}

State::~State()
{
    delete[] state;
}

float * State::get(int param, int x, int y, int z)
{
    int index = size*param;
    index += x;
    index += y*dimSize;
    index += z*pow(dimSize,2);
    return &state[index];
}

State& State::operator=( const State& rhs )
{
    int fullSize = rhs.size * rhs.paramsCount;
    dimSize = rhs.dimSize;
    dim = rhs.dim;
    size = rhs.size;
    paramsCount = rhs.paramsCount;

    if (state != 0) {
        delete[] state;
        state = 0;
    }
    state = new float[fullSize];
    for ( int x = 0; x < fullSize; x++)
        state[x] = rhs.state[x];

    return *this;
}
