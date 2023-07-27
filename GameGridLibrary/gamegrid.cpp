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

std::shared_ptr<GameGrid::CellRow> GameGrid::buildRow(int y)
{
    std::shared_ptr<CellRow> newRow = std::make_shared<CellRow>();
    for (int i = 0; i < width(); ++i) {
        if (m_allowEmptyCells)
            newRow->push_back(std::shared_ptr<GridCell>());
        else
            newRow->push_back(std::make_shared<GridCell>(i + m_xOffset, y));
    }
    return newRow;
}

void GameGrid::appendRow()
{
    setHeight(height() + 1);
    m_rows.push_back(buildRow(maxY()));
}

void GameGrid::prependRow()
{
    --m_yOffset;
    setHeight(height() + 1);
    m_rows.push_front(buildRow(minY()));
}

std::shared_ptr<GridCell> GameGrid::addCell(int x, int y, const std::shared_ptr<GridCell> value)
{
    if (value) {
        value->setX(x);
        value->setY(y);
    }

    // Fist make sure that we have a row and cell to place this in
    // if allowEmptyCells is disabled, cells will be created as the rows/columns are
    while (x >= width() + m_xOffset) {
        appendColumn();
    }

    while (x < m_xOffset) {
        prependColumn();
    }

    while (y >= height() + m_yOffset) {
        appendRow();
    }

    while (y < m_yOffset) {
        prependRow();
    }

    auto row = m_rows.at(y - m_yOffset);
    if (row) {
        row->at(x - m_xOffset) = value;
    }
}

void GameGrid::addCell(int x, int y)
{
    addCell(x, y, std::make_shared<GridCell>(x, y));
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
