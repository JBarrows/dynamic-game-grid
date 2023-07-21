#ifndef GAMEGRID_H
#define GAMEGRID_H

#include "gridcell.h"

#include <deque>

class GameGrid
{
    typedef std::deque<std::shared_ptr<GridCell>> CellRow;

public:
    GameGrid();
    GameGrid(bool allowEmptyCells);

    int width() const;
    int height() const;
    int minX() const;
    int maxX() const;
    int minY() const;
    int maxY() const;

    void addCell(int x, int y, const std::shared_ptr<GridCell> value);
    void addCell(int x, int y);

    std::shared_ptr<GridCell> getCell(int x, int y) const;

    template <class T> std::shared_ptr<T> getComponentAt(int x, int y) {
        std::shared_ptr<GridCell> cell = getCell(x, y);
        return cell ? cell->getComponent<T>() : nullptr;
    };

private:
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    void appendColumn();
    void prependColumn();
    void appendRow();
    void prependRow();
    std::shared_ptr<CellRow> buildRow();

    bool m_allowEmptyCells;
    int m_width, m_height;
    int m_xOffset, m_yOffset;

    std::deque<std::shared_ptr<CellRow>> m_rows;
};

#endif // GAMEGRID_H
