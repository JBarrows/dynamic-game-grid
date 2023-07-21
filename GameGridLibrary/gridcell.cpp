#include "gridcell.h"
#include "cellcomponent.h"

#include <iostream>
#include <typeinfo>

GridCell::GridCell()
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
