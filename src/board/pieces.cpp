#include "pieces.h"


/****************************************** Constructors *****************************************/
// default everything to zero except type for default constructor
Piece::Piece(const BasicPieces type)
    : piece_type(type)

{

}

// copy constructor
Piece::Piece(const Piece& piece_obj) 
    : piece_type(piece_obj.get_type())
{

}

Piece::~Piece() {
    // do nothing right now
}


/*************************************** Getters and Setters *************************************/
const BasicPieces Piece::get_type() const {
    return piece_type;
}

void Piece::set_type(const BasicPieces new_type) {
    piece_type = new_type;
}


/************************************************* Operators *************************************************/
const bool Piece::operator==(const Piece& to_compare) const {
    return get_type() == to_compare.get_type();
}

const bool Piece::operator!=(const Piece& to_compare) const {
    return get_type() != to_compare.get_type();
}

