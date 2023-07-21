#include "victoryoverlay.h"

#include <QPainter>

VictoryOverlay::VictoryOverlay(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    if (parent) {
        resize(parent->size());
    }
}

void VictoryOverlay::addLine(float x1, float y1, float x2, float y2)
{
    m_lines << QLineF(x1, y1, x2, y2);
    update();
}

void VictoryOverlay::reset()
{
    m_lines.clear();
    update();
}

void VictoryOverlay::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.setPen(QPen{QColor{255, 201, 31}, 6});
    for (const QLineF &line : m_lines) {
        QLine newLine {
                (line.p1() * width()).toPoint(),
                (line.p2() * width()).toPoint()
        };
        paint.drawLine(newLine);
    }
}
