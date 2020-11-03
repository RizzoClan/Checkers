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
        /**
         * @Brief: Move a piece on the board
         * @Args: start -> end
         * @Returns: MoveReturns enum (MoveReturns::Invalid == error), see enum for other meanings
         * @Note: Different from base board because has to handle jumping over and removal of enemy pieces
         * @Note: Pieces move diagonally forward (backward if kinged)
         */
        virtual const MoveReturns movePiece(const int start_x, const int start_y, const int end_x, const int end_y);

        
        /**
         * @Brief: Check if "to_compare" is an enemy piece to src
         * @Args: src: Piece that is being compared relative to
         * @Args: to_compare: Piece that is being check if is enemy to src
         * @Return: True (1) for is enemy, False (0) if on same team
         * @Note: True for (Red, White), (White, Red), (White, Black), (Black, White)
         */
        virtual const bool isEnemyPiece(const Piece& src, const Piece& to_compare) const;
    private:
        /********************************************** Helper Functions **********************************************/

};

#endif
