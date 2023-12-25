#include "piece.h"
#include <QFont>
#include <QFontMetrics>
#include <QPainter>

Piece::Piece(std::string character_code, int id, int width): character_code(character_code), id(id), width(width) {
    // setFlag(ItemIsSelectable); // Enable item selection
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

    QPixmap pixmap(size.width(), size.height());
    pixmap.fill(Qt::transparent);

    painter->setFont(font);
    painter->setPen(Qt::black);

    // Calculate the position for center alignment
    int x = (pixmap.width() - size.width()) / 2; // Center horizontally
    int y = (pixmap.height() + metrics.ascent() - metrics.descent()) / 2; // Center vertically

    painter->drawText(x, y, QString::fromStdString(character_code));
}
