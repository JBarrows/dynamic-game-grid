#include "xocomponent.h"

XOComponent::XOComponent()
    : CellComponent()
    , m_state(Empty)
{

}

void XOComponent::setState(State newState)
{
    m_state = newState;
}
