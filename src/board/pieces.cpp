#include "pieces.h"


/****************************************** Constructors *****************************************/
// default everything to zero except type for default constructor
Piece::Piece(const BasicPieces type)
    : Piece(0, 0, type)
{

}


Piece::Piece(const int start_x, const int start_y, const BasicPieces type)
    : pos_x(start_x)
    , pos_y(start_y)
    , piece_type(type)
{

}

Piece::~Piece() {
    // do nothing right now
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

const BasicPieces Piece::get_type() const {
    return piece_type;
}

void Piece::set_type(const BasicPieces new_type) {
    piece_type = new_type;
}

