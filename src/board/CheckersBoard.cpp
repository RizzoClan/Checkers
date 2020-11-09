#include "CheckersBoard.h"

namespace Checkers {


using std::cout;
using std::cerr;
using std::endl;

/**************************************************** Constructors ***************************************************/
CheckersBoard::CheckersBoard()
    // can set the board size to be standard size
    : Board(Constants::standard_checkers_length, Constants::standard_checkers_height)
    , board_pieces(getLength(), std::vector<CheckersPiece>(getHeight(), CheckersPiece()))
{

}

CheckersBoard::~CheckersBoard() {
    // stub
}

/******************************************** Getters and Setters ********************************************/


/********************************************* Board Functions  *********************************************/

}; // end of Checkers namespace
