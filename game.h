#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QPointF>

class Board; // forward declaration

class Game: public QGraphicsView
{
    Q_OBJECT

public slots:
    void use_move(QPointF start_pos, QPointF end_pos);

public:
    Game(QWidget *parent = 0);
    QGraphicsScene *scene;

    std::vector<std::vector<int>> state;
    double board_width;

private:
    bool check_valid_move(int i1, int j1, int i2, int j2);
    bool check_check(int color);
    bool check_checkmate(int color);
    void show_checkmate_dialog(int color);
    int evaluate_board();
    int get_value(int i1, int j1);
    int play_bot_move(int depth);

    // 1 for white, -1 for black
    int turn = 1;
};

#endif // GAME_H
