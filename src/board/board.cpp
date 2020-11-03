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

// const and non-const getBoard functions
const std::vector<std::vector<Piece>>& Board::getBoard() const { return board_pieces; }
std::vector<std::vector<Piece>>& Board::getBoard() { return board_pieces; }


/********************************************* Board Functions  *********************************************/
const bool Board::insertPiece(const int x, const int y, BasicPieces type) {
    // check if spot is empty
    if (getBoard()[x][y].get_type() == BasicPieces::Empty) {
        getBoard()[x][y].set_type(type);
        return true;
    } else {
        return false;
    }
}

const bool Board::movePiece(const int start_x, const int start_y, const int end_x, const int end_y) {
    getBoard()[end_x][end_y] = getBoard()[start_x][start_y];
    getBoard()[start_x][start_y] = Piece(); // reset
}

const bool Board::removePiece(const int x, const int y, const BasicPieces replace_with) {
    if (getBoard()[x][y].get_type() == BasicPieces::Empty) {
        return false; // nothing to remove
    } else {
        getBoard()[x][y] = Piece(replace_with); // reset
        return true;
    }
}



// print
std::ostream& operator<<(std::ostream& os, const Board& this_board) {
    // multiply by 4 because each cell has "| # ...|"
    // extra on right is to round off border
    std::string top_bot_border {std::string(this_board.getLength()*4, '-') + '-'};

    // count row to print for board (decrement so that (0,0) occurs on bottom left corner)
    int row {this_board.getHeight() - 1};

    for(auto& col_vec : this_board.getBoard()) {

        // print the top border between rows (print the char for each col)
        os << top_bot_border << endl;

        for (auto& piece : col_vec) {
            os << "| " << static_cast<char>(piece.get_type()) << " ";
        }

        // print right most border when done with line
        os << "| " << row << endl;

        // decrement row counter
        --row;
    }
    // print the bottom border at end
    os << top_bot_border << endl;

    // print column #s: "| # |" -> "  #  "
    for (int col_num = 0; col_num < this_board.getLength(); col_num++) {
        os << "  " + std::to_string(col_num) + " ";
    }
    os << endl; // go to newline after printing column numbers

    return os;
}


/********************************************* Helper Functions  *********************************************/

