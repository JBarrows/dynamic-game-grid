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
    std::shared_ptr<GridCell> cell;
    if (c == 0) {
        // Add default cell
        cell = grid.addCell(x, y);
    } else {
        // Add cell with a FirstComponent
        auto cellTemplate = std::make_shared<GridCell>(0, 0);
        cellTemplate->addComponent(std::make_shared<FirstComponent>());
        cell = grid.addCell(x, y, cellTemplate);
        if (cell && !cell->getComponent<FirstComponent>()) {
            std::cout << "Failed to retrieve FirstComponent from " << x << ',' << y << std::endl;
        }
    }

    if (cell)
        std::cout << "addCell() added cell at (" << cell->x() << ',' << cell->y() << ')' << std::endl;
    else
        std::cout << "addCell() failed to add cell at (" << x << ',' << y << ')' << std::endl;

    cell = grid.getCell(x, y);
    if (!cell) {
        std::cout << "Failed to get cell at " << x << ',' << y << std::endl;
    }

    if (c < 2)
        return;

    // Try to add one or more of SecondComponent after creation
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

    // Add new cells orthogonally
    addCell(1, 0, grid, 1);
    addCell(-1,0, grid, 1);
    addCell(0, 1, grid, 1);
    addCell(0,-1, grid, 1);
    printGrid(grid);

    // Add new cells diagonally
    addCell(3, 4, grid, 3);
    addCell(-3,-4,grid, 3);
    addCell(-5,6, grid, 0);
    addCell(5,-6, grid, 0);
    printGrid(grid);

    // Add cells within our bounds
    addCell(2, 1, grid, 2);
    addCell(-2,-1,grid, 2);
    addCell(-1,2, grid, 2);
    addCell(1,-2, grid, 2);
    printGrid(grid);

    return 0;
}
