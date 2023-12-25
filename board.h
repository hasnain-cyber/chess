#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>

class Game; // forward declaration

class Board : public QGraphicsItemGroup {
public:
    Board(Game *game);
    void drawPieces(Game *game);
    void updateBoard(Game* game);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    double board_width;
    QList<QMetaObject::Connection> connections;
};

#endif // BOARD_H
