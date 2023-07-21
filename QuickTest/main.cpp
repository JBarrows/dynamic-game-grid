#include <iomanip>
#include <iostream>

#include "../GameGridLibrary/gamegrid.h"
#include "../GameGridLibrary/cellcomponent.h"

class FirstComponent : public CellComponent {
public:
    virtual ~FirstComponent() override {}
};

class SecondComponent : public CellComponent {
public:
    virtual ~SecondComponent() override {}
};

void printGrid(GameGrid &grid)
{
    // First print a header (X values)
    std::cout << std::endl << "   ";
    for (int col = grid.minX(); col <= grid.maxX(); ++col) {
        std::cout << std::setw(3) << (col);
    }
    std::cout << std::endl;

    // Print rows
    for (int row = grid.maxY(); row >= grid.minY(); --row) {
        // First print the row number
        std::cout << std::setw(3) << row;
        for (int col = grid.minX(); col <= grid.maxX(); ++col) {
            auto cell = grid.getCell(col, row);
            if (cell)
                // Print the number of components in each cell
                std::cout << std::setw(3) << cell->components().size();
            else
                std::cout << std::setw(3) << "";
        }
        std::cout << std::endl;
    }
    std::cout << "END" << std::endl;
}

// Adds a cell to grid at x, y and adds c components to it
void addCell(int x, int y, GameGrid &grid, int c = 1)
{
    std::cout << "addCell() adding cell at " << x << ',' << y << std::endl;
    grid.addCell(x, y);
    std::cout << "addCell() added cell at " << x << ',' << y << std::endl;
    if (c < 1)
        return; // EXIT: Don't add components

    auto cell = grid.getCell(x, y);
    if (!cell) {
        std::cout << "Failed to get cell at " << x << ',' << y << std::endl;
    }
    cell->addComponent(std::make_shared<FirstComponent>());
    if (!cell->getComponent<FirstComponent>()) {
        std::cout << "Failed to retrieve FirstComponent from " << x << ',' << y << std::endl;
    }

    if (c < 2)
        return;

    static std::shared_ptr<SecondComponent> secondComponent = std::make_shared<SecondComponent>();
    // Only one of each type of component is allowed, so any number of loops c > 2 are expected to be ineffective
    for (int i = 1; i < c; ++i) {
        std::shared_ptr<SecondComponent> newComponent = std::make_shared<SecondComponent>();
        cell->addComponent(newComponent);
        if (!cell->getComponent<SecondComponent>()) {
            std::cout << "Failed to retrieve SecondComponent from " << x << ' ' << y << std::endl;
        }
    }
}

int main(int argc, char *argv[])
{
    GameGrid grid(true);
    printGrid(grid);

    addCell(2, -2, grid, 2);
    printGrid(grid);

    addCell(-2, 2, grid, 2);
    printGrid(grid);

    addCell(1, 1, grid);
    addCell(-1, -1, grid);
    printGrid(grid);

    addCell(3, 4, grid, 0);
    printGrid(grid);

    addCell(-5, -6, grid, 3);
    printGrid(grid);

    return 0;
}
