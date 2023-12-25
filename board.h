#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <vector>

class Board : public QGraphicsItemGroup {
public:
    Board(double width, std::vector<std::vector<int>> &state);
    void drawPieces(std::vector<std::vector<int>> &state);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    double width; // Width of the board
    std::vector<QGraphicsPixmapItem*> pieces;
};

#endif // BOARD_H
