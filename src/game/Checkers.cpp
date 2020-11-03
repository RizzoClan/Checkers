// Standard Includes
#include <iostream>
#include <string>
#include <sstream>

// 3rd Party Includes

// Our Includes
#include "board.h"
#include "CheckersLogic.h"
#include "constants.h"

using std::cout;
using std::cerr;
using std::endl;


int main(int argc, char* argv[]) {
    // declare board object
    Board checkers_board(standard_checkers_length, standard_checkers_height);

    bool insert_rtn {true};
    insert_rtn &= checkers_board.insertPiece(1,1, BasicPieces::Black);
    insert_rtn &= checkers_board.insertPiece(1,1, BasicPieces::White);


    // complete program
    exit(EXIT_SUCCESS);
}