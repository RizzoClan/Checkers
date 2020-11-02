#ifndef BOARD_H
#define BOARD_H

// Standard Includes
#include <string>
#include <sstream>

// 3rd Party Includes

// Our Includes
#include "game_piece.h"

class Board {
    public:
        /************************************************ Constructors ***********************************************/
        Board(const int length, const int height);


        /******************************************** Getters and Setters ********************************************/
        void setLength(const int new_length);
        void setHeight(const int new_height);
        const int getLength() const;
        const int getHeight() const;

    private:
        int length; // x
        int height; // y

};

#endif
