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

    bool rtn_code {true};
    rtn_code = checkers_board.insertPiece(0,0, BasicPieces::Black);
    if (!rtn_code) {
        cerr << "Error inserting piece" << endl;
    }

    cout << "Board Start: " << endl << checkers_board << endl;

    rtn_code = checkers_board.movePiece(0,0, 1,1) == MoveReturns::Success;
    if (!rtn_code) {
        cerr << "Error moving piece" << endl;
    }

    cout << "After Move: " << endl << checkers_board << endl;

    rtn_code = checkers_board.removePiece(1,1, BasicPieces::Empty);
    if (!rtn_code) {
        cerr << "Error removing piece" << endl;
    }

    cout << "After Remove: " << endl << checkers_board << endl;

    // complete program
    exit(EXIT_SUCCESS);
}