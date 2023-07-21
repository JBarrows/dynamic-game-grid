#include "cellwidget.h"

#include <iostream>
#include <QPainter>
#include <XOComponent.h>

CellWidget::CellWidget(QWidget *parent)
    : QAbstractButton{parent}
    , m_size(80)
    , m_xo(nullptr)
{
    setFixedSize(m_size, m_size);
}

CellWidget::CellWidget(std::shared_ptr<GridCell> cell, const int size, QWidget *parent)
    : QAbstractButton{parent}
    , m_gridCell(cell)
    , m_size(size)
{
    setFixedSize(m_size, m_size);
    setXOComponent();
}

void CellWidget::paintEvent(QPaintEvent *event)
{
    if (!m_gridCell) {
        std::cout << "Paint: No Cell" << std::endl;
        return;
    }

    // Draw background
    QBrush brush(Qt::white);
    if (isX())
        brush.setColor(QColor(255, 63, 31));
    else if (isO())
        brush.setColor(QColor(31, 63, 255));

    QPainter paint(this);
    paint.setBrush(brush);
    paint.setPen(QPen{Qt::black, 4, Qt::SolidLine, Qt::PenCapStyle::FlatCap});
    paint.drawRect(this->rect());
    paint.drawRect(0, 0, 80, 80);

    if (isEmpty())
        return; // EXIT: Don't need to draw a symbol

    // Draw symbol (X, O)
    static int margin = 16;
    paint.setPen(QPen{ Qt::white, 12 });
    if (isX()) {
        paint.drawLine(QLine {
                           {margin, margin},
                           {width() - margin, height() - margin}
                       });
        paint.drawLine(QLine {
                           {width() - margin, margin},
                           {margin, height() - margin}
                       });
    } else if (isO()) {
        paint.drawEllipse(QRect{
                              margin, margin,
                              width() - 2*margin, height() - 2*margin
                          });
    }
}

void CellWidget::setXOComponent()
{
    if (!m_gridCell)
        return;

    std::shared_ptr<XOComponent> component = m_gridCell->getComponent<XOComponent>();
    if (!component) {
        component = std::make_shared<XOComponent>();
        m_gridCell->addComponent(component);
    }

    m_xo = component;
}

void CellWidget::setGridCell(const std::shared_ptr<GridCell> &newGridCell)
{
    m_gridCell = newGridCell;
    setXOComponent();
}

XOComponent::State CellWidget::state() const
{
    if (!m_xo)
        return XOComponent::Empty;

    return m_xo->state();
}

void CellWidget::setState(XOComponent::State state)
{
    if (!m_gridCell)
        return;

    if (!m_xo)
        return;

    m_xo->setState(state);
    update();
}
