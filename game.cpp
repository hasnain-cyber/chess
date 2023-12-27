#include "game.h"
#include <piece.h>
#include <board.h>
#include <QDebug>
#include <QMessageBox>
#include <vector>

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

bool Game::check_valid_move(int i1, int j1, int i2, int j2) {
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

    return valid;
}

void Game::use_move(QPointF start_pos, QPointF end_pos) {
    double side_width = board_width / 8.0;
    int i1 = start_pos.y() / side_width;
    int j1 = start_pos.x() / side_width;
    int i2 = end_pos.y() / side_width;
    int j2 = end_pos.x() / side_width;

    if (check_valid_move(i1, j1, i2, j2)) {
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

    turn *= -1;

    if (check_checkmate(-1)) {
        show_checkmate_dialog(1);
        return;
    }

    if (check_checkmate(1)) {
        show_checkmate_dialog(-1);
        return;
    }

    // if it is black's turn, use bot to play a move
    if (turn == -1) {
        play_bot_move(2);
    }
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

void Game::show_checkmate_dialog(int color) {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Game Over");

    if (color == 1) {
        msgBox.setText("Checkmate! White wins!");
    } else {
        msgBox.setText("Checkmate! Black wins!");
    }

    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

int Game::get_value(int i, int j) {
    int piece_value = state[i][j];

    int value = 0;
    switch (abs(piece_value)) {
    case 1: // Pawn
        value = 2;
        break;
    case 3: // Bishop
    case 4: // Rook
        value = 10;
        break;
    case 2: // Knight
        value = 20;
        break;
    case 5: // Queen
        value = 50;
        break;
    case 6: // King
        value = 100; // Value for king
        break;
    default:
        // Handle invalid piece or empty square
        break;
    }

    return value * (piece_value > 0 ? 1: -1);
}

int Game::evaluate_board() {
    if (check_checkmate(1)) {
        return -10000; // white is checkmated
    } else if (check_checkmate(-1)) {
        return 10000; // black is checkmated
    }

    int total_value = 0;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int piece_value = get_value(i, j);
            total_value += piece_value;
        }
    }

    return total_value;
}

int Game::play_bot_move(int depth) {
    if (depth == 0) return evaluate_board();

    int best_move = INT_MIN; // Initialize with a low value for maximizing

    // Variables to store the best move positions
    int best_i = -1, best_j = -1, best_i2 = -1, best_j2 = -1;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if (turn * state[i][j] > 0) {
                switch(abs(state[i][j])) {
                case 1: // Pawn
                {
                    std::vector<int> di = {-1 * turn, -1 * turn, -1 * turn, -2 * turn}, dj = {0, 1, -1, 0};
                    for(int k = 0; k < 3; k++) {
                        int i2 = i + di[k], j2 = j + dj[k];
                        if (check_valid_move(i, j, i2, j2)) {
                            int temp = state[i2][j2];
                            state[i2][j2] = state[i][j];
                            state[i][j] = 0;

                            int move_value = turn * play_bot_move(depth - 1);

                            state[i][j] = state[i2][j2];
                            state[i2][j2] = temp;

                            if (move_value > best_move) {
                                best_move = move_value;
                                // Store the best move positions
                                best_i = i;
                                best_j = j;
                                best_i2 = i2;
                                best_j2 = j2;
                            }
                        }
                    }
                }
                break;
                case 2: // Knight
                {
                    std::vector<int> di = {-2, -1, 1, 2, 2, 1, -1, -2};
                    std::vector<int> dj = {1, 2, 2, 1, -1, -2, -2, -1};
                    for (int k = 0; k < 8; ++k) {
                        int i2 = i + di[k], j2 = j + dj[k];
                        if (i2 < 0 || i2 >= 8 || j2 < 0 || j2 >= 8) continue; // Out of bounds
                        if (check_valid_move(i, j, i2, j2)) {
                            int temp = state[i2][j2];
                            state[i2][j2] = state[i][j];
                            state[i][j] = 0;

                            int move_value = turn * play_bot_move(depth - 1);

                            state[i][j] = state[i2][j2];
                            state[i2][j2] = temp;

                            if (move_value > best_move) {
                                best_move = move_value;
                                // Store the best move positions
                                best_i = i;
                                best_j = j;
                                best_i2 = i2;
                                best_j2 = j2;
                            }
                        }
                    }
                }
                break;
                // Inside the switch statement for different pieces
                case 3: // Bishop
                {
                    std::vector<int> di = {-1, -1, 1, 1}, dj = {-1, 1, -1, 1};
                    for (int k = 0; k < 4; k++) {
                        for (int step = 1; step < 8; step++) {
                            int i2 = i + di[k] * step, j2 = j + dj[k] * step;
                            if (i2 < 0 || i2 >= 8 || j2 < 0 || j2 >= 8) break; // Out of bounds
                            if (check_valid_move(i, j, i2, j2)) {
                                int temp = state[i2][j2];
                                state[i2][j2] = state[i][j];
                                state[i][j] = 0;

                                int move_value = turn * play_bot_move(depth - 1);

                                state[i][j] = state[i2][j2];
                                state[i2][j2] = temp;

                                if (move_value > best_move) {
                                    best_move = move_value;
                                    // Store the best move positions
                                    best_i = i;
                                    best_j = j;
                                    best_i2 = i2;
                                    best_j2 = j2;
                                }
                            }
                            if (state[i2][j2] != 0) break; // Occupied square, stop this direction
                        }
                    }
                }
                break;
                case 4: // Rook
                {
                    std::vector<int> di = {-1, 1, 0, 0}, dj = {0, 0, -1, 1};
                    for (int k = 0; k < 4; k++) {
                        for (int step = 1; step < 8; step++) {
                            int i2 = i + di[k] * step, j2 = j + dj[k] * step;
                            if (i2 < 0 || i2 >= 8 || j2 < 0 || j2 >= 8) break; // Out of bounds
                            if (check_valid_move(i, j, i2, j2)) {
                                int temp = state[i2][j2];
                                state[i2][j2] = state[i][j];
                                state[i][j] = 0;

                                int move_value = turn * play_bot_move(depth - 1);

                                state[i][j] = state[i2][j2];
                                state[i2][j2] = temp;

                                if (move_value > best_move) {
                                    best_move = move_value;
                                    // Store the best move positions
                                    best_i = i;
                                    best_j = j;
                                    best_i2 = i2;
                                    best_j2 = j2;
                                }
                            }
                            if (state[i2][j2] != 0) break; // Occupied square, stop this direction
                        }
                    }
                }
                break;
                // Inside the switch statement for different pieces
                case 5: // Queen
                {
                    std::vector<int> di = {-1, -1, -1, 0, 0, 1, 1, 1};
                    std::vector<int> dj = {-1, 0, 1, -1, 1, -1, 0, 1};
                    for (int k = 0; k < 8; ++k) {
                        int i2 = i, j2 = j;
                        while (true) {
                            i2 += di[k];
                            j2 += dj[k];
                            if (i2 < 0 || i2 >= 8 || j2 < 0 || j2 >= 8) break; // Out of bounds
                            if (check_valid_move(i, j, i2, j2)) {
                                int temp = state[i2][j2];
                                state[i2][j2] = state[i][j];
                                state[i][j] = 0;

                                int move_value = turn * play_bot_move(depth - 1);

                                state[i][j] = state[i2][j2];
                                state[i2][j2] = temp;

                                if (move_value > best_move) {
                                    best_move = move_value;
                                    // Store the best move positions
                                    best_i = i;
                                    best_j = j;
                                    best_i2 = i2;
                                    best_j2 = j2;
                                }

                                if (state[i2][j2] != 0) break; // Cannot move past a non-empty square
                            } else {
                                break; // Invalid move
                            }
                        }
                    }
                }
                break;
                // Inside the switch statement for different pieces
                case 6: // King
                {
                    std::vector<int> di = {-1, -1, -1, 0, 0, 1, 1, 1};
                    std::vector<int> dj = {-1, 0, 1, -1, 1, -1, 0, 1};
                    for (int k = 0; k < 8; ++k) {
                        int i2 = i + di[k], j2 = j + dj[k];
                        if (i2 < 0 || i2 >= 8 || j2 < 0 || j2 >= 8) continue; // Out of bounds
                        if (check_valid_move(i, j, i2, j2)) {
                            int temp = state[i2][j2];
                            state[i2][j2] = state[i][j];
                            state[i][j] = 0;

                            int move_value = turn * play_bot_move(depth - 1);

                            state[i][j] = state[i2][j2];
                            state[i2][j2] = temp;

                            if (move_value > best_move) {
                                best_move = move_value;
                                // Store the best move positions
                                best_i = i;
                                best_j = j;
                                best_i2 = i2;
                                best_j2 = j2;
                            }
                        }
                    }
                }
                break;
                default:
                    break;
                }
            }
        }
    }

    // After evaluating all possible moves, if a best move is found, execute it
    if (best_i != -1 && best_j != -1 && best_i2 != -1 && best_j2 != -1) {
        // Create QPointF positions for the best move
        double side_width = board_width / 8.0;
        QPointF start_pos(best_j * side_width, best_i * side_width);
        QPointF end_pos(best_j2 * side_width, best_i2 * side_width);

        // Call use_move with the best move positions
        use_move(start_pos, end_pos);
    }

    return best_move;
}
