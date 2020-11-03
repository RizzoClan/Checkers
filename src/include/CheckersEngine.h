#ifndef CHECKERS_ENGINE_H
#define CHECKERS_ENGINE_H

// Standard Includes
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// 3rd Party Includes

// Our Includes
#include "CheckersBoard.h"
#include "constants.h"

class CheckersEngine : CheckersBoard {
    public:
        /************************************************ Constructors ***********************************************/
        CheckersEngine();
        virtual ~CheckersEngine();


        /********************************************** Board Functions **********************************************/
        /**
         * @Brief: Move a piece on the board and combines with parent move to chain moves as needed
         * @Args: start -> end
         * @Returns: MoveReturns enum (MoveReturns::Invalid == error), see enum for other meanings
         */
        virtual const MoveReturns movePiece(const int start_x, const int start_y, const int end_x, const int end_y);

    private:
        /********************************************* Private Variables *********************************************/


        /********************************************** Helper Functions *********************************************/

        /**
         * @Brief: Checks if the piece has an attackable piece next to it
         * @Returns: true: has attackable piece adjacent to it, false cannot attack any pieces
         */
        const bool canAttack(const int x, const int y) const;
};


#endif
