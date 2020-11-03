#ifndef BOARD_H
#define BOARD_H

// Standard Includes
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// 3rd Party Includes

// Our Includes

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
        const std::vector<std::vector<int>>& getBoard() const;

        /********************************************** Board Fucntions **********************************************/

        /**
         * @Brief: Insert a piece on the board
         * @Note: 0 denotes empty space
         */
        const bool insertPiece(const int x, const int y, const int type);

        /**
         * @Brief: Allow ostream to overwrite '<<' so it can be used to print board with cout
         */
        friend std::ostream& operator<<(std::ostream& os, const Board this_board);

    private:
        int length; // x
        int height; // y
        // board needs 2D array to represent all pieces
        std::vector<std::vector<int>> board_pieces;

        /********************************************** Helper Fucntions **********************************************/

};

#endif
