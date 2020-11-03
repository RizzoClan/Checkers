#include "pieces.h"


/****************************************** Constructors *****************************************/
// default everything to zero except type for default constructor
Piece::Piece(const BasicPieces type)
    : piece_type(type)

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

