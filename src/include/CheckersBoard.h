#ifndef CHECKER_BOARD_H
#define CHECKER_BOARD_H

// Standard Includes
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// 3rd Party Includes

// Our Includes
#include "pieces.h"
#include "board.h"

class CheckersBoard : public Board {
    public:
        /************************************************ Constructors ***********************************************/
        CheckersBoard();
        virtual ~CheckersBoard();

        /********************************************** Board Functions **********************************************/


    private:
        /********************************************** Helper Functions **********************************************/

};

#endif
