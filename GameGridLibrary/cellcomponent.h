#ifndef CELLCOMPONENT_H
#define CELLCOMPONENT_H

#include <memory>

class CellComponent
{
public:
    CellComponent();

    virtual ~CellComponent() = default;

    virtual std::shared_ptr<CellComponent> clone() const { return std::make_shared<CellComponent>(*this); }

};

#endif // CELLCOMPONENT_H
