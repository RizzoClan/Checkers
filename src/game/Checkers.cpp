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

    cout << "Starting Board: " << endl << checkers_board << endl;

}