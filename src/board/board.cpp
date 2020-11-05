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

int Board::getLength() const {
    return length;
}

int Board::getHeight() const {
    return height;
}

const Piece& Board::getPiece(int x, int y) const {
    return getBoard()[x][y];
}


// const and non-const getBoard functions
const std::vector<std::vector<Piece>>& Board::getBoard() const { return board_pieces; }
std::vector<std::vector<Piece>>& Board::getBoard() { return board_pieces; }


/********************************************* Board Functions  *********************************************/
bool Board::resetBoard() {
    for (auto& row : getBoard()) {
        for (auto& cell : row) {
            cell = Piece();
        }
    }
    return true;
}

bool Board::isEmpty(const int x, const int y) const {
    return getBoard()[x][y].isEmpty();
}

bool Board::insertPiece(const int x, const int y, BasicPieces type) {
    // check if spot is empty
    if (getBoard()[x][y].isEmpty()) {
        getBoard()[x][y].setType(type);
        return true;
    } else {
        return false;
    }
}

MoveReturns Board::movePiece(const int start_x, const int start_y, const int end_x, const int end_y) {
    const Piece& src_piece = getBoard()[start_x][start_y];
    Piece& dest_piece = getBoard()[end_x][end_y];

    if (!src_piece.isEmpty() && dest_piece.isEmpty()) {
        dest_piece = src_piece;
        getBoard()[start_x][start_y] = Piece(); // reset
        return MoveReturns::Success;
    } else {
        return MoveReturns::Invalid;
    }
}

bool Board::removePiece(const int x, const int y, const BasicPieces replace_with) {
    if (getBoard()[x][y].getType() == BasicPieces::Empty) {
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

    // increment y's first to print one row at a time
    for (int y = 0; y < this_board.getHeight(); y++) {
        // print the top border between rows (print the char for each col)
        os << top_bot_border << endl;

        for (int x = 0; x < this_board.getLength(); x++) {
            os << "| " << static_cast<char>(this_board.getPiece(x,y).getType()) << " ";
        }

        // print right most border when done with line
        os << "| " << y << endl;
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

std::string Board::createCoordStr(const int x, const int y) const {
    return " (" + std::to_string(x) + ',' + std::to_string(y) + ") ";
}
