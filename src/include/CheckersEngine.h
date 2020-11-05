//@File: Handles game logic & rules
//@Note: Rules found at https://ctycms.com/mn-rochester/docs/checkers-instructions.pdf

#ifndef CHECKERS_ENGINE_H
#define CHECKERS_ENGINE_H

// Standard Includes
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <map>
#include <math.h>

// 3rd Party Includes

// Our Includes
#include "Board.h"
#include "constants.h"
#include "CheckersPlayer.h"
#include "PrintEnums.hpp"
#include "common.hpp"

namespace Checkers {

enum class SelectCodes {
    Success,
    CannotMove, // i.e. its not your piece
    Invalid
};

/**
 * Handles the returns from selectPiece
 * @param: Includes (x,y) coordinate and the code for whether or not its a valid piece to select
 */
struct PieceSelectReturns {
    PieceSelectReturns(const SelectCodes rtn_code, const int sel_x, const int sel_y)
        : code(rtn_code), x(sel_x), y(sel_y) {}
    SelectCodes code;
    int x;
    int y;
};

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
        virtual MoveReturns movePiece(const int start_x, const int start_y, const int end_x, const int end_y);
        virtual MoveReturns movePiece(const int start_x, const int start_y);

        /**
         * @Brief: Ask user for coords to select a piece
         * @Returns: PieceSelectReturns::Success for no problems,
         *      PieceSelectReturns::CannotMove for its not your piece,
         *      and PieceSelectReturns::Invalid for everything else
         */
        virtual PieceSelectReturns selectPiece();

        /**
         * @Brief: Ask user for coords for where to move a piece
         * @Args: src x and y are optional and enable print of src->dest (default to -1)
         * @Returns: PieceSelectReturns::Success for no problems,
         *      PieceSelectReturns::CannotMove spot is already taken,
         *      and PieceSelectReturns::Invalid for everything else
         * @Note: Function keeps going until the SelectCodes == SelectCodes::Success -- no need to check
         */
        virtual PieceSelectReturns selectMoveDest(const int src_x=-1, const int src_y=-1);

        virtual bool resetBoard();

    private:
        /********************************************* Private Variables *********************************************/
        // maps piece types to players
        std::map<BasicPieces, CheckersPlayer> piece_to_player;

        /******************************************* Helper Board Functions ******************************************/

        /**
         * @Brief: Checks if the piece has an attackable piece next to it
         * @Returns: true: has attackable piece adjacent to it, false cannot attack any pieces
         */
        bool canAttack(const int x, const int y) const;


        /**
         * @Brief: Checks if the piece can jump over a piece in a specific spot
         * @args: (x,y): the coordinates of the source piece
         * @args: slope: the slope being checked (valid if either 1 or -1)
         * @args: isUpward: true - if piece is going the up board, false - if piece is going down the board 
         * @Returns: true: has attackable piece adjacent to it, false cannot attack any pieces
         */
        bool isJumpable(const int x, const int y, const int slope, const bool is_upward) const;

        /**
         * @Brief: Move a piece on the board
         * @Args: start -> end
         * @Returns: MoveReturns enum (MoveReturns::Invalid == error), see enum for other meanings
         * @Note: Different from base board because has to handle jumping over and removal of enemy pieces
         * @Note: Pieces move diagonally forward (backward if kinged)
         */
        MoveReturns tryMove(const int start_x, const int start_y, const int end_x, const int end_y);

        /**
         * @Brief: Check if "to_compare" is an enemy piece to src
         * @Args: src: Piece that is being compared relative to
         * @Args: to_compare: Piece that is being check if is enemy to src
         * @Return: True (1) for is enemy, False (0) if on same team
         * @Note: True for (Red, White), (White, Red), (White, Black), (Black, White)
         */
        virtual bool isEnemyPiece(const Piece& src, const Piece& to_compare) const;

        /**
         * @Brief: Helps place a player's pieces on the board correctly
         * @Args: player - The player to init on the board
         * @Returns: true for success, false for failure
         */
        virtual bool initPlayerOnBoard(const CheckersPlayer& player);

        /**
         * @Brief: Checks if move is valid based on src->dest and player who is moving
         * @Return: true = is okay, false = invalid move
         * @Note: Invalid could mean player tried to move piece opposite of allowed direction
         */
        virtual bool isValidMoveDir(const CheckersPlayer& player, const BoardCoord src, const BoardCoord dest) const;
};

} // end of Checkers namespace


#endif
