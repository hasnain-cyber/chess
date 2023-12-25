#include "board.h"
#include <piece.h>
#include <game.h>
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

Board::Board(double width, std::vector<std::vector<int>> &state) : width(width) {
    drawPieces(state);
}

void Board::drawPieces(std::vector<std::vector<int>> &state) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int pieceId = state[i][j];
            if (pieceId != 0) { // -1 indicates an empty tile
                std::string character_code;
                switch (pieceId) {
                case -1:
                    character_code = "\u2659"; // Black Pawn
                    break;
                case -2:
                    character_code = "\u2658"; // Black Knight
                    break;
                case -3:
                    character_code = "\u2657"; // Black Bishop
                    break;
                case -4:
                    character_code = "\u2656"; // Black Rook
                    break;
                case -5:
                    character_code = "\u2655"; // Black Queen
                    break;
                case -6:
                    character_code = "\u2654"; // Black King
                    break;
                case 1:
                    character_code = "\u265F"; // White Pawn
                    break;
                case 2:
                    character_code = "\u265E"; // White Knight
                    break;
                case 3:
                    character_code = "\u265D"; // White Bishop
                    break;
                case 4:
                    character_code = "\u265C"; // White Rook
                    break;
                case 5:
                    character_code = "\u265B"; // White Queen
                    break;
                case 6:
                    character_code = "\u265A"; // White King
                    break;
                default:
                    character_code = "\u25A1"; // Empty Tile
                    break;
                }

                double side_width = width / 8.0;
                Piece* piece = new Piece(character_code, pieceId, side_width);
                piece->setPos(j * side_width, (7 - i) * side_width);
                addToGroup(piece);
            }
        }
    }
}

QRectF Board::boundingRect() const {
    // Calculate the combined bounding rect of the board and pieces
    QRectF boardBoundingRect = QRectF(0, 0, width, width);
    for (auto pixmapItem : pieces) {
        boardBoundingRect = boardBoundingRect.united(pixmapItem->boundingRect());
    }
    return boardBoundingRect;
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    double side_length = width / 8;

    // Drawing the chessboard
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            painter->save();
            painter->setPen(Qt::NoPen);
            painter->setBrush(QBrush(((i + j) & 1) ? Qt::darkGray : Qt::white));
            painter->drawRect(j * side_length, i * side_length, side_length, side_length);
            painter->restore();
        }
    }
}
