#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <QGraphicsItem>

class Piece : public QGraphicsItem {
public:
    Piece(std::string character_code = "\u003F", int id = 0, int width = 100);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    std::string character_code;
    int id;
    int width;
};

#endif // PIECE_H
