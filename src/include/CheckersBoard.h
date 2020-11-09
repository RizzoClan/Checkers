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

// explicit instantiation to compile .cpp for the CheckersPiece class
template class BaseBoard::Board<Checkers::CheckersPiece>;

namespace Checkers {


class CheckersBoard : public BaseBoard::Board<CheckersPiece> {

    public:
        /************************************************ Constructors ***********************************************/
        CheckersBoard();
        virtual ~CheckersBoard();


        /******************************************** Getters and Setters ********************************************/

        /********************************************** Board Functions **********************************************/
        // make child define what this means
        virtual bool isEnemyPiece(const CheckersPiece& src, const CheckersPiece& to_compare) const = 0;

    private:
        /********************************************** Helper Functions *********************************************/


    protected:

}; // end of CheckersBoard class

}; // end of Checkers namespace


#endif