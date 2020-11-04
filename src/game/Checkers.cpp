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


// int main(int argc, char* argv[]) {
int main() {
    // declare board object
    CheckersEngine checkers_game;

    bool rtn_code {true};
    rtn_code = checkers_game.insertPiece(0,0, BasicPieces::Black); // piece to move for double jump
    rtn_code = checkers_game.insertPiece(1,1, BasicPieces::White);
    rtn_code = checkers_game.insertPiece(3,3, BasicPieces::White); // piece to double jump

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