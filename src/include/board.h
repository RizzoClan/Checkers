#ifndef BOARD_H
#define BOARD_H

// Standard Includes
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// 3rd Party Includes

// Our Includes
#include "pieces.h"

class Board {
    public:
        /************************************************ Constructors ***********************************************/
        Board(const int length, const int height);
        virtual ~Board();


        /******************************************** Getters and Setters ********************************************/
        void setLength(const int new_length);
        void setHeight(const int new_height);
        const int getLength() const;
        const int getHeight() const;
        const std::vector<std::vector<Piece>>& getBoard() const;

        /********************************************** Board Functions **********************************************/

        /**
         * @Brief: Insert a piece on the board
         * @Return: True (1) for success, False (0) if spot taken already
         */
        virtual const bool insertPiece(const int x, const int y, BasicPieces type);

        /**
         * @Brief: Removes a piece on the board
         * @Args: replace_with: (Defaults to empty), use this to replace removed piece with a specific one
         * @Return: True (1) for success, False (0) if spot was empty
         */
        virtual const bool removePiece(const int x, const int y, const BasicPieces replace_with=BasicPieces::Empty);

        /**
         * @Brief: Move a piece on the board
         * @Args: start -> end
         */
        virtual const bool movePiece(const int start_x, const int start_y, const int end_x, const int end_y);


        /**
         * @Brief: Allow ostream to overwrite '<<' so it can be used to print board with cout
         */
        friend std::ostream& operator<<(std::ostream& os, const Board& this_board);

    private:
        int length; // x
        int height; // y
        // board needs 2D array to represent all pieces
        std::vector<std::vector<Piece>> board_pieces;

        /********************************************** Helper Functions **********************************************/

};

#endif
