#include <iostream>

#include "gamegrid.h"

GameGrid::GameGrid()
    : m_allowEmptyCells(false)
    , m_width(0), m_height(0)
    , m_xOffset(0), m_yOffset(0)
{
    addCell(0, 0);
}

GameGrid::GameGrid(bool allowEmptyCells)
    : m_allowEmptyCells(allowEmptyCells)
    , m_width(0), m_height(0)
    , m_xOffset(0), m_yOffset(0)
{
    if (allowEmptyCells) {
        // Begin with a null cell
        addCell(0, 0, nullptr);
    } else {
        // Begin with a cell at 0,0
        addCell(0, 0);
    }
}

int GameGrid::width() const
{
    return m_width;
}

int GameGrid::height() const
{
    return m_height;
}

int GameGrid::minX() const
{
    return m_xOffset;
}

int GameGrid::maxX() const
{
    return width() + m_xOffset - 1;
}

int GameGrid::minY() const
{
    return m_yOffset;
}

int GameGrid::maxY() const
{
    return height() + m_yOffset - 1;
}


void GameGrid::setWidth(int newWidth)
{
    if (m_width == newWidth)
        return;
    m_width = newWidth;
}

void GameGrid::setHeight(int newHeight)
{
    if (m_height == newHeight)
        return;
    m_height = newHeight;
}

void GameGrid::appendColumn()
{
    setWidth(width() + 1);
    // Add cell to each row
    int y = minY();
    for(auto row : m_rows) {
        if (m_allowEmptyCells) {
            row->push_back(std::shared_ptr<GridCell>());
        } else {
            auto newCell = std::make_shared<GridCell>(maxX(), y);
            row->push_back(newCell);
        }
        ++y;
    }
}

std::shared_ptr<GridCell> GameGrid::appendColumn(std::shared_ptr<GridCell> cell, int targetY)
{
    std::shared_ptr<GridCell> targetCell;
    setWidth(width() + 1);
    // Append a cell to each row
    int y = minY();
    for (auto row : m_rows) {
        std::shared_ptr<GridCell> newCell;

        // Shared w/ prependColumn
        if (y == targetY) {
            // Add the given cell
            newCell = cell;
            targetCell = newCell;
        } else if (m_allowEmptyCells) {
            // Add a null cell to pad out the grid (Technically this is already done)
            newCell = nullptr;
        } else {
            // Add a default cell to pad out the grid
            newCell = std::make_shared<GridCell>(maxX(), y);
        }
        ++y;
        // \shared

        row->push_back(newCell);
    }

    return targetCell;
}

void GameGrid::prependColumn()
{
    --m_xOffset;
    setWidth(width() + 1);
    // Prepend cell to each row
    int y = minY();
    for(auto row : m_rows) {
        if (m_allowEmptyCells) {
            row->push_front(std::shared_ptr<GridCell>());
        } else {
            row->push_front(std::make_shared<GridCell>(maxX(), y));
            ++y;
        }
    }
}

std::shared_ptr<GridCell> GameGrid::prependColumn(std::shared_ptr<GridCell> cell, int targetY)
{
    std::shared_ptr<GridCell> targetCell;
    --m_xOffset;
    setWidth(width() + 1);
    // Prepend a cell to each row
    int y = minY();
    for(auto row : m_rows) {
        std::shared_ptr<GridCell> newCell;

        // Shared w/ appendColumn
        if (y == targetY) {
            // Add the given cell
            newCell = cell;
            targetCell = newCell;
        } else if (m_allowEmptyCells) {
            // Add a null cell to pad out the grid (Technically this is already done)
            newCell = nullptr;
        } else {
            // Add a default cell to pad out the grid
            newCell = std::make_shared<GridCell>(maxX(), y);
        }
        ++y;
        // \shared

        row->push_front(newCell);
    }
    return targetCell;
}

std::shared_ptr<GameGrid::CellRow> GameGrid::buildRow(int y)
{
    std::shared_ptr<CellRow> newRow = std::make_shared<CellRow>();

    for (int i = minX(); i <= maxX(); ++i) {
        std::shared_ptr<GridCell> newCell;
        if (!m_allowEmptyCells)
            newCell = std::make_shared<GridCell>(i, y);

        newRow->push_back(newCell);
    }

    return newRow;
}

std::shared_ptr<GameGrid::CellRow> GameGrid::buildRow(std::shared_ptr<GridCell> cell, int targetX, int y, std::shared_ptr<GridCell> &outCell)
{
    std::shared_ptr<CellRow> newRow = std::make_shared<CellRow>();

    for (int x = minX(); x <= maxX(); ++x) {
        std::shared_ptr<GridCell> newCell;
        if (x == targetX) {
            newCell = cell;
        } else if (m_allowEmptyCells) {
            // Add a null cell to pad out the grid (Technically this is already done)
            newCell = nullptr;
        } else {
            // Add a default cell to pad out the grid
            newCell = std::make_shared<GridCell>(x, y);
        }

        newRow->push_back(newCell);
        if (x == targetX) {
            outCell = newCell;
        }
    }

    return newRow;
}

void GameGrid::appendRow()
{
    setHeight(height() + 1);
    auto newRow = buildRow(maxY());
    m_rows.push_back(newRow);
}

std::shared_ptr<GridCell> GameGrid::appendRow(std::shared_ptr<GridCell> cell, int targetX)
{
    std::shared_ptr<GridCell> newCell;

    setHeight(height() + 1);
    auto newRow = buildRow(cell, targetX, maxY(), newCell);
    m_rows.push_back(newRow);

    return newCell;
}

void GameGrid::prependRow()
{
    --m_yOffset;
    setHeight(height() + 1);
    auto newRow = buildRow(minY());
    m_rows.push_front(newRow);
}

std::shared_ptr<GridCell> GameGrid::prependRow(std::shared_ptr<GridCell> cell, int targetX)
{
    std::shared_ptr<GridCell> newCell;

    --m_yOffset;
    setHeight(height() + 1);
    auto newRow = buildRow(cell, targetX, minY(), newCell);
    m_rows.push_front(newRow);

    return newCell;
}

std::shared_ptr<GridCell> GameGrid::addCell(int x, int y, const std::shared_ptr<GridCell> value)
{
    std::shared_ptr<GridCell> newCell;

    if (value) {
        value->setX(x);
        value->setY(y);
    }

    // Fist make sure that we have a row and cell to place this in
    // if allowEmptyCells is disabled, cells will be created as the rows/columns are
    while (x >= width() + m_xOffset) {
        if (x == width() + m_xOffset) {
            newCell = appendColumn(value, y);
            // Can't return yet, the row may not exist
        } else {
            appendColumn();
        }
    }

    while (x < m_xOffset) {
        if (x+1 == m_xOffset) {
            newCell = prependColumn(value, y);
            // Can't return yet, the row may not exist
        } else {
            prependColumn();
        }
    }

    while (y >= height() + m_yOffset) {
        if (y == height() + m_yOffset) {
            newCell = appendRow(value, x);
        } else {
            appendRow();
        }
    }

    while (y < m_yOffset) {
        if (y+1 == m_yOffset) {
            newCell = prependRow(value, x);
        } else {
            prependRow();
        }
    }

    if (newCell || !value)
        return newCell;

    // If we're still here, x,y were inside our bounds
    auto row = m_rows.at(y - m_yOffset);
    if (row) {
        // Returning the input parameter stinks. We should probably clone the input cell or something
        newCell = value;
        row->at(x - m_xOffset) = value;

        return newCell;
    }

    return nullptr;
}

std::shared_ptr<GridCell> GameGrid::addCell(int x, int y)
{
    return addCell(x, y, std::make_shared<GridCell>(x, y));
}

std::shared_ptr<GridCell> GameGrid::getCell(int x, int y) const
{
    if (x < minX()) {
        return nullptr;
    } if (maxX() < x) {
        return nullptr;
    } if (y < minY()) {
        return nullptr;
    } if (maxY() < y) {
        return nullptr;
    }

    auto row = m_rows.at(y - m_yOffset);
    return row->at(x - m_xOffset);
}
