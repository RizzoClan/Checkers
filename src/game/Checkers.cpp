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
    Checkers::CheckersEngine checkers_game;

    bool rtn_code {true};

    cout << "Board Start: " << endl << checkers_game << endl;

    rtn_code = checkers_game.movePiece(2,5, 3, 4) == MoveReturns::Success; // no error
    rtn_code = checkers_game.movePiece(3, 4, 2,5) == MoveReturns::Success; // error
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