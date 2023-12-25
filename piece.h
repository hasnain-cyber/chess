#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QObject>

class Piece : public QObject, public QGraphicsItem {
    Q_OBJECT

signals:
    void piece_release_signal(QPointF start_pos, QPointF end_pos);

public:
    Piece(std::string character_code = "\u003F", int id = 0, int width = 100);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    std::string character_code;
    int id, width;
    QPointF initial_pos, start_pos;
};

#endif // PIECE_H
