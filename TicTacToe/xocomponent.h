#ifndef XOCOMPONENT_H
#define XOCOMPONENT_H

#include "../GameGridLibrary/cellcomponent.h"

class XOComponent : public CellComponent
{
public:
    enum State { Empty, X, O };

    XOComponent();

    State state() const { return m_state; }
    void setState(State newState);

private:
    State m_state;
};

#endif // XOCOMPONENT_H
