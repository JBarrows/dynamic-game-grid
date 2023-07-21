#ifndef CELLWIDGET_H
#define CELLWIDGET_H

#include "../GameGridLibrary/gridcell.h"
#include "xocomponent.h"

#include <QAbstractButton>

class CellWidget : public QAbstractButton
{
    Q_OBJECT
public:
    explicit CellWidget(QWidget *parent = nullptr);
    explicit CellWidget(std::shared_ptr<GridCell> cell, const int size, QWidget *parent = nullptr);

    std::shared_ptr<GridCell> gridCell() const { return m_gridCell; }
    void setGridCell(const std::shared_ptr<GridCell> &newGridCell);

    XOComponent::State state() const;
    void setState(XOComponent::State state);
    bool isEmpty() const { return state() == XOComponent::Empty; }
    bool isX() const { return state() == XOComponent::X; }
    bool isO() const { return state() == XOComponent::O; }

signals:

protected:
    void paintEvent(QPaintEvent *event);
    void setXOComponent();

private:
    std::shared_ptr<GridCell> m_gridCell;
    int m_size;
    std::shared_ptr<XOComponent> m_xo;
};

#endif // CELLWIDGET_H
