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

struct BoardCoord {
    BoardCoord(const int x, const int y) : x(x), y(y) {}
    friend std::ostream& operator<<(std::ostream& os, const BoardCoord& this_coord) {
        os << '(' << this_coord.x << ',' << this_coord.y << ')';
        return os;
    };
    int x;
    int y;
};

class Board {
    public:
        /************************************************ Constructors ***********************************************/
        Board(const int length, const int height);
        virtual ~Board();


        /******************************************** Getters and Setters ********************************************/
        void setLength(const int new_length);
        void setHeight(const int new_height);
        int getLength() const;
        int getHeight() const;

        /**
         * @Brief: Get the piece at a given cell
         * @Args: x & y are the coordinates
         * @Note: Used in engines & logic
         */
        const Piece& getPiece(int x, int y) const;

        // need const & non-const types of getBoard() -> one for editing elements, and one for reference only
        const std::vector<std::vector<Piece>>& getBoard() const; // completely const
        std::vector<std::vector<Piece>>& getBoard(); // not const

        /********************************************** Board Functions **********************************************/

        /**
         * @Brief: Insert a piece on the board
         * @Return: True (1) for success, False (0) if spot taken already
         */
        virtual bool insertPiece(const int x, const int y, BasicPieces type);

        /**
         * @Brief: Removes a piece on the board
         * @Args: replace_with: (Defaults to empty), use this to replace removed piece with a specific one
         * @Return: True (1) for success, False (0) if spot was empty
         */
        virtual bool removePiece(const int x, const int y, const BasicPieces replace_with=BasicPieces::Empty);

        /**
         * @Brief: Move a piece on the board
         * @Args: start -> end
         */
        virtual MoveReturns movePiece(const int start_x, const int start_y, const int end_x, const int end_y);

        /**
         * set as completely virtual with '=0'
         * @Brief: Check if "to_compare" is an enemy piece to src
         * @Args: src: Piece that is being compared relative to
         * @Args: to_compare: Piece that is being check if is enemy to src
         * @Return: True (1) for is enemy, False (0) if on same team
         */
        virtual bool isEnemyPiece(const Piece& src, const Piece& to_compare) const = 0;


        /**
         * @Brief: Allow ostream to overwrite '<<' so it can be used to print board with cout
         */
        friend std::ostream& operator<<(std::ostream& os, const Board& this_board);

        bool isEmpty(const int x, const int y) const;

    private:
        int length; // x
        int height; // y
        // board needs 2D array to represent all pieces
        std::vector<std::vector<Piece>> board_pieces;

    protected:
        /********************************************** Helper Functions **********************************************/
        /**
         * @Brief: Creates preformatted string containing " (x,y) "
         * @Note: The string already contains spaces on left and right
         */
        std::string createCoordStr(const int x, const int y) const;
};

#endif
