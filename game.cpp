#include "game.h"
#include <piece.h>
#include <board.h>
#include <QDebug>

Game::Game(QWidget *parent): QGraphicsView(parent) {
    // create scene
    scene = new QGraphicsScene();

    // set scene
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 800);

    // initialise a clean state
    // 0 for empty state
    // 1 for pawn
    // 2 for knight
    // 3 for bishop
    // 4 for rook
    // 5 for queen
    // 6 for king
    state = {
        {-4, -2, -3, -5, -6, -3, -2, -4},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 1,  1,  1,  1,  1,  1,  1,  1},
        { 4,  2,  3,  5,  6,  3,  2,  4}
    };

    // add board
    Board* board = new Board(this->width(), state);
    scene->addItem(board);
}

void Game::mousePressEvent(QMouseEvent *event) {
    qDebug() << "clicked";
}
