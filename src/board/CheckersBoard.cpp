#include "CheckersBoard.h"

using std::cout;
using std::cerr;
using std::endl;

/**************************************************** Constructors ***************************************************/
CheckersBoard::CheckersBoard()
    // checkers baords have to be a specific size 
    : Board(standard_checkers_length, standard_checkers_height)
{

}



CheckersBoard::~CheckersBoard() {}


/********************************************* Board Functions  *********************************************/



/********************************************* Helper Functions  *********************************************/

