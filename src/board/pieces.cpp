#include "pieces.h"


/****************************************** Constructors *****************************************/
// default everything to zero except type for default constructor
Piece::Piece(const BasicPieces type)
    : piece_type(type)

{

}

// copy constructor
Piece::Piece(const Piece& piece_obj) 
    : piece_type(piece_obj.getType())
{

}

Piece::~Piece() {
    // do nothing right now
}


/*************************************** Getters and Setters *************************************/
BasicPieces Piece::getType() const {
    return piece_type;
}

void Piece::setType(const BasicPieces new_type) {
    piece_type = new_type;
}


/************************************************* Operators *************************************************/
bool Piece::operator==(const Piece& to_compare) const {
    return getType() == to_compare.getType();
}

bool Piece::operator!=(const Piece& to_compare) const {
    return getType() != to_compare.getType();
}

std::ostream& operator<<(std::ostream& os, const Piece& this_piece) {
    return os << static_cast<char>(this_piece.getType());
}

bool Piece::operator!=(const BasicPieces& to_compare) const {
    return getType() != to_compare;
}
bool Piece::operator==(const BasicPieces& to_compare) const {
    return getType() == to_compare;

}


/********************************************** Helper Functions **********************************************/
bool Piece::isEmpty() const {
    return getType() == BasicPieces::Empty;
}
