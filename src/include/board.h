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
#include "PrintEnums.hpp"

namespace BaseBoard {

struct BoardCoord {
    BoardCoord(const int x, const int y) : x(x), y(y) {}

    // printing
    friend std::ostream& operator<<(std::ostream& os, const BoardCoord& this_coord) {
        return os << '(' << this_coord.x << ',' << this_coord.y << ')';
    };

    // arithmetic
    friend BoardCoord operator+(const BoardCoord& coord1, const BoardCoord& coord2) {
        return BoardCoord{(coord1.x + coord2.x), (coord1.y + coord2.y)};
    }
    friend BoardCoord operator-(const BoardCoord& coord1, const BoardCoord& coord2) {
        return BoardCoord{(coord1.x - coord2.x), (coord1.y - coord2.y)};
    }

    // actual coordinates
    int x;
    int y;
};

template <class PieceType>
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
        const PieceType& getPiece(int x, int y) const;
        const PieceType& getPiece(const BoardCoord& coord) const;

        // need const & non-const types of getBoard() -> one for editing elements, and one for reference only
        const std::vector<std::vector<PieceType>>& getBoard() const; // completely const
        std::vector<std::vector<PieceType>>& getBoard(); // not const

        /********************************************** Board Functions **********************************************/

        /**
         * @Brief: Wipe the board back to default
         * @Return: true if successful, false if failure
         */
        virtual bool resetBoard();

        /**
         * @Brief: Insert a piece on the board
         * @Return: True (1) for success, False (0) if spot taken already
         */
        virtual bool insertPiece(const int x, const int y, BasicPieces type);

        /**
         * @Brief: Removes a piece on the board
         * @Args: replace_with: (Defaults to empty), use this to replace removed piece with a specific one
         * @Return: The piece type that was removed
         */
        virtual BaseBoard::BasicPieces removePiece(
            const int x, const int y, const BasicPieces replace_with=BasicPieces::Empty);
        virtual BaseBoard::BasicPieces removePiece(
            const BaseBoard::BoardCoord coord, const BasicPieces replace_with=BasicPieces::Empty);

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
        virtual bool isEnemyPiece(const PieceType& src, const PieceType& to_compare) const = 0;


        /**
         * @Brief: Allow ostream to overwrite '<<' so it can be used to print board with cout
         * @HACK in order to work with template class:
         *      inline << function with a reference to "print" class method that can be overriden
         */
        virtual std::ostream& print(std::ostream& os, const Board& this_board) const;
        friend std::ostream& operator<<(std::ostream& os, const Board& this_board) {
            return this_board.print(os, this_board);
        }

        bool isEmpty(const int x, const int y) const;

    private:
        int length; // x
        int height; // y
        // board needs 2D array to represent all pieces
        std::vector<std::vector<PieceType>> board_pieces;

    protected:
        /********************************************** Helper Functions **********************************************/
        /**
         * @Brief: Creates preformatted string containing " (x,y) "
         * @Note: The string already contains spaces on left and right
         */
        std::string createCoordStr(const int x, const int y) const;
};

} // end of BaseBoard namespace


#endif
