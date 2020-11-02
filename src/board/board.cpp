#include "board.h"

/**************************************************** Constructors ***************************************************/
Board::Board(const int new_length, const int new_height)
    : length(new_length)
    , height(new_height)

{

}


/******************************************** Getters and Setters ********************************************/
void Board::setLength(const int new_length) {
    length = new_length;
}

void Board::setHeight(const int new_height) {
    height = new_height;
}

const int Board::getLength() const {
    return length;
}

const int Board::getHeight() const {
    return height;
}
