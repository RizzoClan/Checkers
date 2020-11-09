#ifndef CHECKERS_BOARD_H
#define CHECKERS_BOARD_H

// Standard Includes
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// 3rd Party Includes

// Our Includes
#include "board.h"
#include "CheckersPieces.h"
#include "PrintEnums.hpp"

namespace Checkers {

class CheckersBoard : public BaseBoard::Board {

    public:
        /************************************************ Constructors ***********************************************/
        CheckersBoard();
        virtual ~CheckersBoard();


        /******************************************** Getters and Setters ********************************************/

        /********************************************** Board Functions **********************************************/
    private:
        /********************************************** Helper Functions *********************************************/


    protected:
        // board needs 2D array to represent all pieces
        std::vector<std::vector<CheckersPiece>> board_pieces;

}; // end of CheckersBoard class

}; // end of Checkers namespace


#endif