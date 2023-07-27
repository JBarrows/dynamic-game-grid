#ifndef GRIDCELL_H
#define GRIDCELL_H

#include "cellcomponent.h"
#include <iostream>
#include <map>
#include <memory>
#include <typeindex>

typedef std::map<std::type_index, std::shared_ptr<CellComponent>> ComponentMap;

class GridCell
{
public:
    GridCell(int x = 0, int y = 0);

    const ComponentMap &components() const { return m_components; }

    /// \note Only one component of each type is allowed
    bool addComponent(std::shared_ptr<CellComponent> component);

    /// Components are retrieved by passing the type as a template
    template <class T> std::shared_ptr<T> getComponent()  {
        std::type_index typeIndex = typeid(T);
        if (m_components.count(typeIndex) < 1) {
            //std::cout << "getComponent: Not found " << typeIndex.name() << typeIndex.hash_code() << std::endl;
            return nullptr;
        }
        auto component = m_components.at(typeIndex);
        return std::static_pointer_cast<T>(component);
    };

    int x() const { return m_x; }
    void setX(int newX);

    int y() const { return m_y; }
    void setY(int newY);

private:
    /// \note We map the components by type_index, but for the interface we use template arguments which are much easier to read and include
    ComponentMap m_components;
    int m_x;
    int m_y;
};

#endif // GRIDCELL_H
