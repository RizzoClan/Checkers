// Standard Includes
#include <iostream>
#include <string>
#include <sstream>

// 3rd Party Includes

// Our Includes
#include "CheckersEngine.h"
#include "constants.h"

using std::cout;
using std::cerr;
using std::endl;


int main(int argc, char* argv[]) {
    // declare board object
    CheckersEngine checkers_game;

    bool rtn_code {true};
    rtn_code = checkers_game.insertPiece(0,0, BasicPieces::Black);
    rtn_code = checkers_game.insertPiece(1,1, BasicPieces::White);

    cout << "Board Start: " << endl << checkers_game << endl;

    rtn_code = checkers_game.movePiece(0,0) == MoveReturns::Success;
    if (!rtn_code) {
        cerr << "Error moving piece" << endl;
    }

    // rtn_code = checkers_game.removePiece(1,1, BasicPieces::Empty);
    // if (!rtn_code) {
    //     cerr << "Error removing piece" << endl;
    // }

    // cout << "After Remove: " << endl << checkers_game << endl;

    // complete program
    exit(EXIT_SUCCESS);
}