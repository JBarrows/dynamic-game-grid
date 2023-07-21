#include "board.h"
#include "victoryoverlay.h"

#include "../GameGridLibrary/gridcell.h"

#include <QPaintEvent>
#include <QPainter>

const int CELL_SIZE(80);

Board::Board(QWidget *parent)
    : QWidget{parent}
    , m_currentPlayer(XOComponent::X)
{
    setMinimumWidth(3*CELL_SIZE);
    setMinimumHeight(3*CELL_SIZE);
    m_grid.addCell(-1, -1);
    m_grid.addCell(1, 1);

    // Link each logical GridCell to a visible CellWidget
    for (int x = m_grid.minX(); x <= m_grid.maxX(); ++x) {
        for (int y = m_grid.minY(); y <= m_grid.maxY(); ++y) {
            std::shared_ptr<GridCell> cell = m_grid.getCell(x, y);
            CellWidget* newCell = new CellWidget(cell, CELL_SIZE, this);
            connect(newCell, &CellWidget::clicked,
                    this, &Board::onCellClicked, Qt::QueuedConnection);
            newCell->move((x - m_grid.minX()) * CELL_SIZE, (y - m_grid.minY()) * CELL_SIZE);
            m_cells << newCell;
        }
    }

    // victoryOverlay shows the winning line
    m_victoryOverlay = new VictoryOverlay(this);
}

void Board::reset()
{
    for(auto cellWidget : m_cells) {
        cellWidget->setState(XOComponent::Empty);
    }
    m_victoryOverlay->reset();
    setEnabled(true);
}

XOComponent::State Board::getXOAt(int x, int y)
{
    auto xo = m_grid.getComponentAt<XOComponent>(x, y);

    if (xo)
        return xo->state();
    else
        return XOComponent::Empty;
}

void Board::CheckVictory()
{
    // We only need to check if the current player has won
    // Check each row and column
    for (int i = -1; i <= 1; ++i) {
        bool rowMatch = true;
        bool colMatch = true;

        // check rows
        for (int j = -1; j <= 1; ++j) {
            if (getXOAt(j, i) != m_currentPlayer) {
                rowMatch = false;
                break;
            }
            // The row is matching so far
        }
        if (rowMatch) {
            setEnabled(false);
            std::cout << "Victory on row " << i << std::endl;
            float linePos = (1 + 2 * (i + 1)) / 6.0;
            m_victoryOverlay->addLine(0.05f, linePos, 0.95f, linePos);
        }

        // check columns
        for (int j = -1; j <= 1; ++j) {
            if (getXOAt(i, j) != m_currentPlayer) {
                colMatch = false;
                break;
            }
            // The column is matching so far
        }
        if (colMatch) {
            setEnabled(false);
            std::cout << "Victory on column " << i << std::endl;

            float linePos = (1 + 2 * (i + 1)) / 6.0;
            m_victoryOverlay->addLine(linePos, 0.05f, linePos, 0.95f);
        }
    }

    // Check diagonals
    bool diagDownMatch = true;
    bool diagUpMatch = true;
    for (int i = -1; i <= 1; ++i) {
        if (getXOAt(i, i) != m_currentPlayer) {
            diagDownMatch = false;
        }

        if (getXOAt(-i, i) != m_currentPlayer) {
            diagUpMatch = false;
        }

        if (!diagDownMatch && !diagUpMatch)
            break;
    }
    if (diagDownMatch) {
        setEnabled(false);
        m_victoryOverlay->addLine(0.05f, 0.05f, 0.95f, 0.95f);
        std::cout << "Victory on downward diagonal" << std::endl;
    }
    if (diagUpMatch) {
        setEnabled(false);
        m_victoryOverlay->addLine(0.05f, 0.95f, 0.95f, 0.05f);
        std::cout << "Victory on upward diagonal" << std::endl;
    }
}

void Board::onCellClicked(bool checked)
{
    CellWidget* cell = qobject_cast<CellWidget*>(sender());
    if (!cell)
        return;

    if (!cell->isEmpty())
        return;

    cell->setState(m_currentPlayer);

    // Check for win
    CheckVictory();

    // Go to next player
    m_currentPlayer = (m_currentPlayer == XOComponent::X) ? XOComponent::O : XOComponent::X;
}

void Board::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.setBrush(QBrush(Qt::black));
    paint.drawRect(this->rect());
}
