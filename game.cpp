#include "game.h"
#include <piece.h>
#include <board.h>
#include <QDebug>

Game::Game(QWidget *parent): QGraphicsView(parent) {
    // create scene
    scene = new QGraphicsScene();

    // set board parameters
    board_width = 800;

    // set scene
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(board_width, board_width);

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
    Board* board = new Board(this);
    scene->addItem(board);
}

void Game::check_valid_move(QPointF start_pos, QPointF end_pos) {
    // Convert positions to indices
    double side_width = board_width / 8.0;
    int i1 = start_pos.y() / side_width;
    int j1 = start_pos.x() / side_width;
    int i2 = end_pos.y() / side_width;
    int j2 = end_pos.x() / side_width;

    bool valid = false;
    switch (state[i1][j1]) {
    case 1:
        // pawn
        valid = (i2 == i1 - 1 && j1 == j2) || (i2 == i1 - 2 && i1 == 6 && j1 == j2); // simple move
        valid |= (j1 + 1 <= 7 && state[i1 - 1][j1 + 1] < 0) || (j1 - 1 >= 0 && state[i1 - 1][j1 - 1] < 0); // diagonal capture
        break;
    case 2:
        // knight
        valid = (abs(i2 - i1) == 2 && abs(j2 - j1) == 1) || (abs(j2 - j1) == 2 && abs(i2 - i1) == 1);
        break;
    case 3:
        // bishop
        valid = abs(i2 - i1) == abs(j2 - j1);
        break;
    case 4:
        // rook
        valid = (i1 == i2 && j1 != j2) || (i1 != i2 && j1 == j2);
        break;
    case 5:
        // queen
        valid = (i1 == i2 && j1 != j2) ||(i1 != i2 && j1 == j2) || (abs(i2 - i1) == abs(j2 - j1));
        break;
    case 6:
        // king
        valid = abs(i2 - i1) <= 1 && abs(j2 - j1) <= 1;
        break;
    default:
        break;
    }

    if (valid) {
        state[i2][j2] = state[i1][j1];
        state[i1][j1] = 0;
    }

    for (QGraphicsItem *item : scene->items()) {
        if (Board *board = dynamic_cast<Board*>(item)) {
            board->updateBoard(this);
            break;
        }
    }
}

