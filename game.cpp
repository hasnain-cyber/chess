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
    // state = {
    //     {-4, -2, -3, -5, -6, -3, -2, -4},
    //     {-1, -1, -1, -1, -1, -1, -1, -1},
    //     { 0,  0,  0,  0,  0,  0,  0,  0},
    //     { 0,  0,  0,  0,  0,  0,  0,  0},
    //     { 0,  0,  0,  0,  0,  0,  0,  0},
    //     { 0,  0,  0,  0,  0,  0,  0,  0},
    //     { 1,  1,  1,  1,  1,  1,  1,  1},
    //     { 4,  2,  3,  5,  6,  3,  2,  4}
    // };
    state = {
        { 0,  0,  0,  0,  -6,  0,  0,  0},
        { 0,  0,  0,  0,  -5,  0,  0,  4},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  4,  0,  0,  0},
        { 0,  0,  0,  0,  6,  0,  0,  0}
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

    bool valid;
    switch (abs(state[i1][j1])) {
    case 1:
        // pawn
        if ((i1 == 6 && i2 == 4 && j1 == j2 && state[i2][j2] == 0 && state[i1 - 1][j1] == 0 && state[i1][j1] > 0) || // double move for white
            (i1 == 1 && i2 == 3 && j1 == j2 && state[i2][j2] == 0 && state[i1 + 1][j1] == 0 && state[i2][j2] < 0) || // double move for black
            (i2 == i1 - 1 && j1 == j2 && state[i2][j2] == 0  && state[i1][j1] > 0) || // simple move for white pawn
            (i2 == i1 - 1 && abs(j2 - j1) == 1 && state[i2][j2] * state[i1][j1] < 0) || // diagonal capture for white pawn
            (i2 == i1 + 1 && j1 == j2 && state[i2][j2] == 0  && state[i2][j2] < 0) || // simple move for black pawn
            (i2 == i1 + 1 && abs(j2 - j1) == 1 && state[i2][j2] * state[i1][j1] < 0 && state[i1][j1] < 0)) // diagonal capture for black pawn
        {
            valid = true;
        } else {
            valid = false;
        }
        break;
    case 2:
        // knight
        valid = (abs(i2 - i1) == 2 && abs(j2 - j1) == 1) || (abs(j2 - j1) == 2 && abs(i2 - i1) == 1);
        break;
    case 3:
        // bishop
        if (abs(i2 - i1) == abs(j2 - j1)) {
            int i_step = (i2 - i1) > 0 ? 1 : -1;
            int j_step = (j2 - j1) > 0 ? 1 : -1;

            bool flag = true;
            for (int i = i1 + i_step, j = j1 + j_step; i != i2; i += i_step, j += j_step) {
                if (state[i][j] != 0) {
                    flag = false;
                    break;
                }
            }
            valid = flag;
        } else {
            valid = false;
        }
        break;
    case 4:
        // rook
        if (i1 == i2) {
            int j_step = (j2 - j1) > 0 ? 1 : -1;
            bool flag = true;
            for (int j = j1 + j_step; j != j2; j += j_step) {
                if (state[i1][j] != 0) {
                    flag = false;
                    break;
                }
            }
            valid = flag;
        } else if (j1 == j2) {
            int i_step = (i2 - i1) > 0 ? 1 : -1;
            bool flag = true;
            for (int i = i1 + i_step; i != i2; i += i_step) {
                if (state[i][j1] != 0) {
                    flag = false;
                    break;
                }
            }
            valid = flag;
        } else {
            valid = false;
        }
        break;
    case 5:
        // queen
        if (i1 == i2 || j1 == j2 || abs(i2 - i1) == abs(j2 - j1)) {
            int i_step = (i2 - i1) > 0 ? 1 : ((i2 - i1) < 0 ? -1 : 0);
            int j_step = (j2 - j1) > 0 ? 1 : ((j2 - j1) < 0 ? -1 : 0);

            bool flag = true;
            if (i1 == i2 || j1 == j2) {
                for (int i = i1 + i_step, j = j1 + j_step; i != i2 || j != j2; i += i_step, j += j_step) {
                    if (state[i][j] != 0) {
                        flag = false;
                        break;
                    }
                }
            } else {
                for (int i = i1 + i_step, j = j1 + j_step; i != i2; i += i_step, j += j_step) {
                    if (state[i][j] != 0) {
                        flag = false;
                        break;
                    }
                }
            }
            valid = flag;
        } else {
            valid = false;
        }
        break;
    case 6:
        // king
        valid = abs(i2 - i1) <= 1 && abs(j2 - j1) <= 1;
        break;
    default:
        valid = false;
        break;
    }

    // should be an empty tile or enemy piece.
    valid &= (state[i2][j2] * state[i1][j1] <= 0);

    // should not be on the same tile
    valid &= (!(i1 == i2 && j1 == j2));

    if (valid) {
        state[i2][j2] = state[i1][j1];
        state[i1][j1] = 0;
    }

    // update board
    for (QGraphicsItem *item : scene->items()) {
        if (Board *board = dynamic_cast<Board*>(item)) {
            board->updateBoard(this);
            break;
        }
    }

    qDebug() << check_checkmate(-1);
}

// 1 for white, -1 for black
bool Game::check_check(int color) {
    int kingRow = -1, kingCol = -1;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if (state[i][j] == color * 6) {
                kingRow = i, kingCol = j;
                break;
            }
        }
    }

    if (kingCol == -1 && kingRow == -1) {
        return false;
    }

    // Check if any opponent's pieces can attack the king
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (state[i][j] * color < 0) { // Opponent's piece
                switch (abs(state[i][j])) {
                case 1: // Pawn
                    // Check if the pawn can attack the king
                    if ((i == kingRow + color) && (j == kingCol + 1 || j == kingCol - 1)) {
                        return true; // King is in check
                    }
                    break;
                case 2: // Knight
                    // Check if the knight can attack the king
                    if ((abs(i - kingRow) == 2 && abs(j - kingCol) == 1) || (abs(j - kingCol) == 2 && abs(i - kingRow) == 1)) {
                        return true; // King is in check
                    }
                    break;
                case 3: // Bishop
                    // Check if the bishop can attack the king
                    if (abs(i - kingRow) == abs(j - kingCol)) {
                        int i_step = (i - kingRow) > 0 ? 1 : -1;
                        int j_step = (j - kingCol) > 0 ? 1 : -1;

                        bool flag = true;
                        for (int m = kingRow + i_step, n = kingCol + j_step; m != i; m += i_step, n += j_step) {
                            if (state[m][n] != 0) {
                                flag = false;
                                break;
                            }
                        }
                        if (flag) {
                            return true; // King is in check
                        }
                    }
                    break;
                case 4: // Rook
                    // Check if the rook can attack the king
                    if ((i == kingRow && j != kingCol) || (i != kingRow && j == kingCol)) {
                        int i_step = (i == kingRow) ? 0 : (i - kingRow) / abs(i - kingRow);
                        int j_step = (j == kingCol) ? 0 : (j - kingCol) / abs(j - kingCol);

                        bool flag = true;
                        for (int m = kingRow + i_step, n = kingCol + j_step; m != i || n != j; m += i_step, n += j_step) {
                            if (state[m][n] != 0 && (m != i || n != j)) {
                                flag = false;
                                break;
                            }
                        }
                        if (flag) {
                            return true; // King is in check
                        }
                    }
                    break;
                case 5: // Queen
                    // Check if the queen can attack the king (combining bishop and rook logic)
                    if ((i == kingRow || j == kingCol || abs(i - kingRow) == abs(j - kingCol))) {
                        int i_step = (i == kingRow) ? 0 : (i - kingRow) / abs(i - kingRow);
                        int j_step = (j == kingCol) ? 0 : (j - kingCol) / abs(j - kingCol);

                        bool flag = true;
                        for (int m = kingRow + i_step, n = kingCol + j_step; m != i || n != j; m += i_step, n += j_step) {
                            if (state[m][n] != 0 && (m != i || n != j)) {
                                flag = false;
                                break;
                            }
                        }
                        if (flag) {
                            return true; // King is in check
                        }
                    }
                    break;
                case 6: // King
                    // Kings can't directly attack each other, so no need to check here
                    break;
                default:
                    break;
                }
            }
        }
    }

    return false; // King is not in check
}

bool Game::check_checkmate(int color) {
    // Get the king's position
    int kingRow = -1, kingCol = -1;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (state[i][j] == color * 6) {
                kingRow = i;
                kingCol = j;
                break;
            }
        }
    }

    if (kingCol == -1 && kingRow == -1) {
        return false; // No king found
    }

    // Check if the king is in check
    if (!check_check(color)) {
        return false; // King is not in check
    }

    // Attempt to move the king in all directions and check if it resolves the check
    for (int i = kingRow - 1; i <= kingRow + 1; ++i) {
        for (int j = kingCol - 1; j <= kingCol + 1; ++j) {
            if ((i == kingRow && j == kingCol) || i < 0 || i >= 8 || j < 0 || j >= 8 || state[i][j] * color > 0) continue;

            // Simulate the move
            int temp = state[i][j];
            state[i][j] = state[kingRow][kingCol];
            state[kingRow][kingCol] = 0;

            // Check if the move resolves the check
            if (!check_check(color)) {
                qDebug() << i << " " << j;
                // Revert the simulated move and return false (not in checkmate)
                state[kingRow][kingCol] = state[i][j];
                state[i][j] = temp;
                return false;
            }

            // Revert the simulated move
            state[kingRow][kingCol] = state[i][j];
            state[i][j] = temp;
        }
    }

    return true; // King is in checkmate
}
