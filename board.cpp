#include "board.h"
#include <QGraphicsRectItem>
#include <piece.h>

Board::Board(QGraphicsScene* scene, double width) : width(width), scene(scene) {}

void Board::drawBoard() {
    double side_length = width / 8;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            QGraphicsRectItem* cell = new QGraphicsRectItem(j * side_length, i * side_length, side_length, side_length);
            cell->setBrush(QBrush(((i + j) & 1) ? Qt::white : Qt::darkGray));

            scene->addItem(cell);
            Piece *piece = NULL;

            if (i == 0) {
                if (j == 0 || j == 7) {
                    piece = new Piece("\u265C", 0); // black rook
                } else if (j == 1 || j == 6) {
                    piece = new Piece("\u265E", 0); // black knight
                } else if (j == 2 || j == 5) {
                    piece = new Piece("\u265D", 0); // black bishop
                } else if (j == 3) {
                    piece = new Piece("\u265B", 0); // black queen
                } else if (j == 4) {
                    piece = new Piece("\u265A", 0); // black king
                }
            } else if (i == 1) {
                piece = new Piece("\u265F", 0); // black pawn
            } else if (i == 6) {
                piece = new Piece("\u2659", 1); // white pawn
            } else if (i == 7) {
                if (j == 0 || j == 7) {
                    piece = new Piece("\u2656", 1); // white rook
                } else if (j == 1 || j == 6) {
                    piece = new Piece("\u2658", 1); // white knight
                } else if (j == 2 || j == 5) {
                    piece = new Piece("\u2657", 1); // white bishop
                } else if (j == 3) {
                    piece = new Piece("\u2655", 1); // white queen
                } else if (j == 4) {
                    piece = new Piece("\u2654", 1); // white king
                }
            }

            if (piece != NULL) {
                QPixmap pixmap = piece->generatePixmapFromCharacterCode();
                QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap);
                pixmapItem->setPos(j * side_length + (side_length - pixmap.width()) / 2, i * side_length + (side_length - pixmap.height()) / 2);

                scene->addItem(pixmapItem);
            }
        }
    }
}
