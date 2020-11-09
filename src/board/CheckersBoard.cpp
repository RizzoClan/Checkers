#include "CheckersBoard.h"
#include "board.cpp"

namespace Checkers {


using std::cout;
using std::cerr;
using std::endl;

/**************************************************** Constructors ***************************************************/
CheckersBoard::CheckersBoard()
    // can set the board size to be standard size
    : Board<CheckersPiece>(
        Constants::standard_checkers_length, Constants::standard_checkers_height)
{

}

CheckersBoard::~CheckersBoard() {
    // stub
}

/******************************************** Getters and Setters ********************************************/


/********************************************* Board Functions  *********************************************/

}; // end of Checkers namespace
