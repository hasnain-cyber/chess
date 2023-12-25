#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QMouseEvent>

class Game: public QGraphicsView
{
public:
    Game(QWidget *parent = 0);
    QGraphicsScene *scene;
    std::vector<std::vector<int>> state;

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // GAME_H
