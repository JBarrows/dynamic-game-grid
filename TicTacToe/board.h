#ifndef BOARD_H
#define BOARD_H

#include "cellwidget.h"
#include "victoryoverlay.h"
#include "xocomponent.h"
#include "../GameGridLibrary/gamegrid.h"

#include <QWidget>

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);

public slots:
    void reset();

signals:

private slots:
    void onCellClicked(bool checked);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

private:
    void CheckVictory();
    XOComponent::State getXOAt(int i, int j);

    XOComponent::State m_currentPlayer;
    GameGrid m_grid;
    VictoryOverlay* m_victoryOverlay;
    QList<CellWidget*> m_cells;
};

#endif // BOARD_H
