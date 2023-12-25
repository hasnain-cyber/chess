#include "piece.h"
#include <QFont>
#include <QFontMetrics>
#include <QPainter>
#include <QCursor>
#include <QApplication>
#include <QDebug>

Piece::Piece(std::string character_code, int id, int width): QObject(), character_code(character_code), id(id), width(width) {
    setFlag(ItemIsSelectable);
}

QRectF Piece::boundingRect() const {
    return QRectF(0, 0, width, width); // Set the bounding rectangle for the piece
}

void Piece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QFont font("Arial", 64);
    QFontMetrics metrics(font);
    QSize size = metrics.size(0, QString::fromStdString(character_code));

    painter->setFont(font);
    painter->setPen(Qt::black);

    // Calculate the position for center alignment
    int x = (boundingRect().width() - size.width()) / 2; // Center horizontally
    int y = (boundingRect().height() + metrics.ascent() - metrics.descent()) / 2; // Center vertically

    painter->drawText(x, y, QString::fromStdString(character_code));
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (id <= 0) return;

    if (event->button() == Qt::LeftButton) {
        initial_pos = start_pos = mapToParent(event->pos()); // Store the absolute scene position
        setCursor(Qt::ClosedHandCursor);
    }

    QGraphicsItem::mousePressEvent(event);
}

void Piece::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (id <= 0) return;

    if (event->buttons() & Qt::LeftButton) {
        QPointF current_scene_pos = mapToParent(event->pos());
        QPointF diff = current_scene_pos - start_pos; // Calculate the difference in scene coordinates

        setPos(mapToParent(diff)); // Adjust the local position using the scene difference
        start_pos = current_scene_pos; // Update the start_pos to the new scene position
    }

    QGraphicsItem::mouseMoveEvent(event);
}

void Piece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (id <= 0) return;

    emit piece_release_signal(initial_pos, mapToParent(event->pos()));
    QGraphicsItem::mouseReleaseEvent(event);
}
