#include "board.h"

using std::cout;
using std::cerr;
using std::endl;

/**************************************************** Constructors ***************************************************/
Board::Board(const int new_length, const int new_height)
    : length(new_length)
    , height(new_height)
    // create 2D vector initialized to 0
    , board_pieces(getLength(), std::vector<Piece>(getHeight(), Piece()))

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

const std::vector<std::vector<Piece>>& Board::getBoard() const {
    return board_pieces;
}


/********************************************* Board Functions  *********************************************/
const bool Board::insertPiece(const int x, const int y, BasicPieces type) {
    board_pieces[x][y].set_type(type);
    return true;
}


// print
std::ostream& operator<<(std::ostream& os, const Board this_board) {
    // multiply by 4 because each cell has "| # ...|"
    // extra on right is to round off border
    std::string top_bot_border {std::string(this_board.getLength()*4, '-') + '-'};

    for(auto& col : this_board.getBoard()) {
        // print the top border between rows (print the char for each col)
        os << top_bot_border << endl;

        for (auto& piece : col) {
            os << "| " << static_cast<char>(piece.get_type()) << " ";
        }

        // print right most border when done with line
        os << "|" << endl;
    }
    // print the bottom border at end
    os << top_bot_border << endl;

    return os;
}


/********************************************* Helper Functions  *********************************************/

