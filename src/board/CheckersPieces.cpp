#include "CheckersPieces.h"

namespace Checkers {


/****************************************** Constructors *****************************************/
CheckersPiece::CheckersPiece(const BaseBoard::BasicPieces type) 
    : Piece(type)
    , isKinged(false)
{
    
}

// copy constructor
CheckersPiece::CheckersPiece(const CheckersPiece& piece_obj)
    : Piece(piece_obj) // call parent copy constructor first
    , isKinged(piece_obj.getIsKinged())
{

}

CheckersPiece::~CheckersPiece() {
    // stub
}

/*************************************** Getters and Setters *************************************/
bool CheckersPiece::getIsKinged() const {
    return isKinged;
}

bool CheckersPiece::setIsKinged(bool new_state) {
    isKinged = new_state;
    return true;
}

/********************************************** Helper Functions **********************************************/

/************************************************* Operators *************************************************/
std::ostream& operator<<(std::ostream& os, const CheckersPiece& this_piece) {
    const auto piece_repr {static_cast<char>(this_piece.getType())};
    // cannot use ternary bc different types
    if (this_piece.getIsKinged()) {
        return os << Printing::underlineChar(piece_repr);
    } else {
        return os << piece_repr;
    }
}


};