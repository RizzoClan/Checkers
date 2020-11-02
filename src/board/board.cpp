#include "board.h"

using std::cout;
using std::cerr;
using std::endl;

/**************************************************** Constructors ***************************************************/
Board::Board(const int new_length, const int new_height)
    : length(new_length)
    , height(new_height)
    // create 2D vector initialized to 0
    , board_pieces(getLength(), std::vector<int>(getHeight(), 0))

{

}


Board::~Board() {

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

const std::vector<std::vector<int>>& Board::getBoard() const {
    return board_pieces;
}


/********************************************* Board Functions  *********************************************/
std::ostream& operator<<(std::ostream& os, const Board this_board) {
    for(auto& col : this_board.getBoard()) {
        // print the top border between rows (print the char for each col)
        os << std::string(this_board.getLength(), '-') << endl;

        for (auto& piece : col) {
            os << "| " << piece;
        }

        // print right most border when done with line
        os << " |" << endl;
    }
    // print the bottom border at end
    os << std::string(this_board.getLength(), '-') << endl;
}


/********************************************* Helper Functions  *********************************************/
/*
bool Board::clearBoard() const {
    for(auto& col : board_pieces) {
    }
}
*/

