#include "piece.h"
#include <QFont>
#include <QFontMetrics>
#include <QPainter>

Piece::Piece(std::string character_code, int color): character_code(character_code), color(color) {}

QPixmap Piece::generatePixmapFromCharacterCode() {
    QFont font("Arial", 64); // Adjust font and size as needed
    QFontMetrics metrics(font);
    QSize size = metrics.size(0, QString::fromStdString(character_code));

    QPixmap pixmap(size.width(), size.height());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setFont(font);
    painter.setPen(Qt::black);

    // Calculate the position for center alignment
    int x = (pixmap.width() - size.width()) / 2; // Center horizontally
    int y = (pixmap.height() + metrics.ascent() - metrics.descent()) / 2; // Center vertically

    painter.drawText(x, y, QString::fromStdString(character_code));

    return pixmap;
}
