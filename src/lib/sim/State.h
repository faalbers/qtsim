#ifndef STATE_H
#define STATE_H

class State
{
public:
    State(int _dimSize, int _dim, int _paramsCount);
    State(const State& other );
    ~State();

    State& operator=( const State& rhs );

    float   *state;
    int     dimSize;
    int     dim;
    int     size;
    int     paramsCount;

    float * get(int param, int x = 0, int y = 0, int z = 0);

private:
    void assign(const State& rhs);
};

#endif // STATE_H
