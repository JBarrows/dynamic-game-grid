#include "gridcell.h"
#include "cellcomponent.h"

#include <iostream>
#include <typeinfo>

GridCell::GridCell(int x, int y)
    : m_x(x)
    , m_y(y)
{

}

bool GridCell::addComponent(std::shared_ptr<CellComponent> component)
{
    const CellComponent &bareComponent = *component;
    std::type_index typeId = typeid(bareComponent);
    if (m_components.count(typeId) > 0) {
        std::cout << "Skipping component " << m_components.size() << " " << typeId.name() << std::endl;
        return false; // Failed to add: component of this type exists
    }
    std::shared_ptr<CellComponent> shared(component);
    m_components[typeId] = shared;
    return true;
}

void GridCell::setX(int newX) {
    m_x = newX;
}

void GridCell::setY(int newY) {
    m_y = newY;
}
