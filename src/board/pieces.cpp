#include "game_piece.h"


/****************************************** Constructors *****************************************/
Piece::Piece(const int start_x, const int start_y, std::string type)
    : pos_x(start_x)
    , pos_y(start_y)
    , piece_type(type)
{

}

/*************************************** Getters and Setters *************************************/
const int Piece::get_x() const {
    return pos_x;
}

const int Piece::get_y() const {
    return pos_y;
}

void Piece::set_x(const int new_x) {
    pos_x = new_x;
}
void Piece::set_y(const int new_y) {
    pos_y = new_y;
}

