#include "game.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>
#include <board.h>

Game::Game(QWidget *parent): QGraphicsView(parent) {
    // create scene
    scene = new QGraphicsScene();

    // set scene
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 800);

    // draw board
    Board* board = new Board(scene, this->width());
    board->drawBoard();
}
