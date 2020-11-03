#ifndef CHECKERS_ENGINE_H
#define CHECKERS_ENGINE_H

// Standard Includes
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// 3rd Party Includes

// Our Includes
#include "Board.h"
#include "constants.h"

class CheckersEngine : public Board {
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


        /******************************************* Helper Board Functions ******************************************/

        /**
         * @Brief: Checks if the piece has an attackable piece next to it
         * @Returns: true: has attackable piece adjacent to it, false cannot attack any pieces
         */
        const bool canAttack(const int x, const int y) const;

        /**
         * @Brief: Move a piece on the board
         * @Args: start -> end
         * @Returns: MoveReturns enum (MoveReturns::Invalid == error), see enum for other meanings
         * @Note: Different from base board because has to handle jumping over and removal of enemy pieces
         * @Note: Pieces move diagonally forward (backward if kinged)
         */
        const MoveReturns tryMove(const int start_x, const int start_y, const int end_x, const int end_y);

        /**
         * @Brief: Check if "to_compare" is an enemy piece to src
         * @Args: src: Piece that is being compared relative to
         * @Args: to_compare: Piece that is being check if is enemy to src
         * @Return: True (1) for is enemy, False (0) if on same team
         * @Note: True for (Red, White), (White, Red), (White, Black), (Black, White)
         */
        virtual const bool isEnemyPiece(const Piece& src, const Piece& to_compare) const;
};


#endif
