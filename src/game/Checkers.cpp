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

    cout << "Board Start: " << endl << checkers_game << endl;

    const BaseBoard::BasicTeams winner {checkers_game.play()};

    cout << "Winner: " << winner << endl;

    // complete program
    exit(EXIT_SUCCESS);
}