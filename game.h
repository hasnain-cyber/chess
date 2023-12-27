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
    void check_valid_move(QPointF start_pos, QPointF end_pos);

public:
    Game(QWidget *parent = 0);
    QGraphicsScene *scene;

    std::vector<std::vector<int>> state;
    double board_width;

private:
    bool check_check(int color);
    bool check_checkmate(int color);
};

#endif // GAME_H
