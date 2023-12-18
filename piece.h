#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <QPixmap>

class Piece
{
public:
    Piece(std::string character_code = "\u003F", int color = 0);
    QPixmap generatePixmapFromCharacterCode();

private:
    std::string character_code;
    // 0 for black, 1 for white
    int color;
};

#endif // PIECE_H
