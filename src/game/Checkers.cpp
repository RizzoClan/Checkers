// Standard Includes
#include <iostream>
#include <string>
#include <sstream>

// 3rd Party Includes

// Our Includes
#include "CheckersBoard.h"
#include "CheckersLogic.h"
#include "constants.h"

using std::cout;
using std::cerr;
using std::endl;


int main(int argc, char* argv[]) {
    // declare board object
    CheckersBoard checkers_board;

    bool insert_rtn {true};
    insert_rtn &= checkers_board.insertPiece(1,1, BasicPieces::Black);

    cout << "Board Start: " << endl << checkers_board << endl;

    insert_rtn &= checkers_board.movePiece(1,1, 2,2);

    cout << "After Move: " << endl << checkers_board << endl;

    // insert_rtn &= checkers_board.removePiece(1,1, BasicPieces::Red);

    // cout << "Board: " << endl << checkers_board << endl;

    // complete program
    exit(EXIT_SUCCESS);
}