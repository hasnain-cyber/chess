#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include <piece.h>

class Board {
public:
    Board(QGraphicsScene* scene, double width);
    void drawBoard();

private:
    int width;
    QGraphicsScene* scene;
    Piece* state[8][8];
};

#endif // BOARD_H
