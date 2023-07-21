#ifndef VICTORYOVERLAY_H
#define VICTORYOVERLAY_H

#include <QWidget>

class VictoryOverlay : public QWidget
{
    Q_OBJECT
    QList<QLineF> m_lines;

public:
    explicit VictoryOverlay(QWidget *parent = nullptr);
    void addLine(float x1, float y1, float x2, float y2);

public slots:
    void reset();

signals:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // VICTORYOVERLAY_H
