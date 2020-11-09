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


};