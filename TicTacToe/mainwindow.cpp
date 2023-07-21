#include "mainwindow.h"
#include "board.h"

#include <QMenuBar>
#include <QPainter>
#include <QPushButton>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Board* board = new Board(this);
    setCentralWidget(board);
    QMenuBar* menu = new QMenuBar(this);
    menu->addAction("Reset", board, &Board::reset);
    setMenuWidget(menu);
}

MainWindow::~MainWindow()
{
}

