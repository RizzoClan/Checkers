#include "board.h"

using std::cout;
using std::cerr;
using std::endl;

namespace BaseBoard {

/**************************************************** Constructors ***************************************************/
template <class PieceType>
Board<PieceType>::Board(const int new_length, const int new_height)
    : length(new_length)
    , height(new_height)
    // create 2D vector initialized to 0
    , board_pieces(getLength(), std::vector<PieceType>(getHeight(), PieceType()))

{

}


template <class PieceType>
Board<PieceType>::~Board() {
}

/******************************************** Getters and Setters ********************************************/
template <class PieceType>
void Board<PieceType>::setLength(const int new_length) {
    length = new_length;
}

template <class PieceType>
void Board<PieceType>::setHeight(const int new_height) {
    height = new_height;
}

template <class PieceType>
int Board<PieceType>::getLength() const {
    return length;
}

template <class PieceType>
int Board<PieceType>::getHeight() const {
    return height;
}

// getPiece() functions
template <class PieceType>
const PieceType& Board<PieceType>::getPiece(const BoardCoord& coord) const {
    return getPiece(coord.x, coord.y);
}

template <class PieceType>
PieceType& Board<PieceType>::getPiece(int x, int y) {
    return getBoard()[x][y];
}

template <class PieceType>
const PieceType& Board<PieceType>::getPiece(int x, int y) const {
    return getBoard()[x][y];
}


// const and non-const getBoard functions
template <class PieceType>
const std::vector<std::vector<PieceType>>& Board<PieceType>::getBoard() const { return board_pieces; }
template <class PieceType>
std::vector<std::vector<PieceType>>& Board<PieceType>::getBoard() { return board_pieces; }


/********************************************* Board Functions  *********************************************/
template <class PieceType>
bool Board<PieceType>::resetBoard() {
    for (auto& row : getBoard()) {
        for (auto& cell : row) {
            cell = PieceType();
        }
    }
    return true;
}

template <class PieceType>
bool Board<PieceType>::isEmpty(const int x, const int y) const {
    return getBoard()[x][y].isEmpty();
}

template <class PieceType>
bool Board<PieceType>::isOutOfBounds(const int x, const int y) const {
    return x < 0 || y < 0 || x >= getLength() || y >= getHeight();
}


template <class PieceType>
bool Board<PieceType>::insertPiece(const int x, const int y, BasicPieces type) {
    // check if spot is empty
    if (getBoard()[x][y].isEmpty()) {
        getBoard()[x][y].setType(type);
        return true;
    } else {
        return false;
    }
}

template <class PieceType>
MoveReturns Board<PieceType>::movePiece(const int start_x, const int start_y, const int end_x, const int end_y) {
    const PieceType& src_piece {getBoard()[start_x][start_y]};
    PieceType& dest_piece {getBoard()[end_x][end_y]};

    if (!src_piece.isEmpty() && dest_piece.isEmpty()) {
        dest_piece = src_piece;
        getBoard()[start_x][start_y] = PieceType(); // reset
        return MoveReturns::Success;
    } else {
        return MoveReturns::Invalid;
    }
}

template <class PieceType>
BaseBoard::BasicPieces Board<PieceType>::removePiece(const BaseBoard::BoardCoord coord, const BasicPieces replace_with) {
    return removePiece(coord.x, coord.y, replace_with);
}

template <class PieceType>
BaseBoard::BasicPieces Board<PieceType>::removePiece(const int x, const int y, const BasicPieces replace_with) {
    const BaseBoard::BasicPieces removed_type {getBoard()[x][y].getType()};
    if (removed_type != BasicPieces::Empty) {
        getBoard()[x][y].setType(replace_with); // reset
    }
    return removed_type;
}

/********************************************* Print Functions  *********************************************/
// print individual cell content
template <class PieceType>
void Board<PieceType>::printCell(
    std::ostream& os, const Board<PieceType>& this_board,
    const int x, const int y
) const {
    os << this_board.getPiece(x,y); // << overload handled by Piece object
}

template <class PieceType>
std::ostream&  Board<PieceType>::print(std::ostream& os, const Board<PieceType>& this_board) const {
    // multiply by 4 because each cell has "| # ...|"
    // extra on right is to round off border
    std::string top_bot_border {std::string(this_board.getLength()*4, '-') + '-'};

    // increment y's first to print one row at a time
    for (int y = 0; y < this_board.getHeight(); y++) {
        // print the top border between rows (print the char for each col)
        os << top_bot_border << endl;

        for (int x = 0; x < this_board.getLength(); x++) {
            os << "| "; // print left border of cell
            this_board.printCell(os, this_board, x, y); // print cell contents
            os << " "; // print space to lead up to next left board
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

template <class PieceType>
std::string Board<PieceType>::createCoordStr(const int x, const int y) const {
    return " (" + std::to_string(x) + ',' + std::to_string(y) + ") ";
}

} // end of BaseBoard namespace

