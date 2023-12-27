#include "board.h"
#include <piece.h>
#include <game.h>
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

Board::Board(Game *game) {
    setHandlesChildEvents(false); // to let the pieces be dragged

    this->board_width = game->board_width;
    updateBoard(game);
}

QRectF Board::boundingRect() const {
    return QRectF(0, 0, board_width, board_width);
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    double side_length = board_width / 8;

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

void Board::updateBoard(Game *game) {
    // clear connections
    for (const auto& connection : connections) {
        QObject::disconnect(connection);
    }
    connections.clear();

    // clear the pieces
    for (auto item : childItems()) {
        removeFromGroup(item);
        delete item;
    }

    // redraw pieces
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int pieceId = game->state[i][j];
            if (pieceId != 0) { // -1 indicates an empty tile
                std::string character_code;
                switch (pieceId) {
                case -1:
                    character_code = "\u265F"; // White Pawn
                    break;
                case -2:
                    character_code = "\u265E"; // White Knight
                    break;
                case -3:
                    character_code = "\u265D"; // White Bishop
                    break;
                case -4:
                    character_code = "\u265C"; // White Rook
                    break;
                case -5:
                    character_code = "\u265B"; // White Queen
                    break;
                case -6:
                    character_code = "\u265A"; // White King
                    break;
                case 1:
                    character_code = "\u2659"; // Black Pawn
                    break;
                case 2:
                    character_code = "\u2658"; // Black Knight
                    break;
                case 3:
                    character_code = "\u2657"; // Black Bishop
                    break;
                case 4:
                    character_code = "\u2656"; // Black Rook
                    break;
                case 5:
                    character_code = "\u2655"; // Black Queen
                    break;
                case 6:
                    character_code = "\u2654"; // Black King
                    break;
                default:
                    character_code = "\u25A1"; // Empty Tile
                    break;
                }

                double side_width = board_width / 8.0;
                Piece *piece = new Piece(character_code, pieceId, side_width);
                piece->setPos(j * side_width, i * side_width);
                addToGroup(piece);
                QMetaObject::Connection connection = QObject::connect(piece, SIGNAL(piece_release_signal(QPointF,QPointF)), game, SLOT(check_valid_move(QPointF,QPointF)));
                connections.append(connection);
            }
        }
    }
}
