#include "CheckersBoard.h"

using std::cout;
using std::cerr;
using std::endl;

/**************************************************** Constructors ***************************************************/
CheckersBoard::CheckersBoard()
    // checkers baords have to be a specific size 
    : Board(standard_checkers_length, standard_checkers_height)
{

}



CheckersBoard::~CheckersBoard() {}


/********************************************* Board Functions  *********************************************/

const bool CheckersBoard::isEnemyPiece(const Piece& src, const Piece& to_compare) const {
    // since there are only two types of pieces (binary coloring), can do a simple !=
    return src != to_compare;
}

// have to overwrite move to handle taking pieces & jumping
const MoveReturns CheckersBoard::movePiece(const int start_x, const int start_y, const int end_x, const int end_y) {
    /**
     * slope of move = diagonal = 1 or -1
     * can only go forward if not king
     */
    const int delta_y = end_y - start_y;
    const int delta_x = end_x - start_x;
    const float move_slope = delta_y / delta_x;
    const bool diag_move = (move_slope == -1 || move_slope == 1);
    if (diag_move) {
        //  get relative pieces
        auto& curr_board = getBoard();
        Piece& src_piece = curr_board[start_x][start_y];
        Piece& dest_piece = curr_board[end_x][end_y];

        //  check if there is a piece in dest or jumping over an enemy
        if (dest_piece.isEmpty() && (delta_y == 1 || delta_y == -1)) {
            // normal move into empty space
            Board::movePiece(start_x, start_y, end_x, end_y);
        } else if (!dest_piece.isEmpty()) {
            cout << "Invalid Move! Moving onto an existing piece" << endl;
            return MoveReturns::Invalid;
        } else if((delta_y == 2 || delta_y == -2) && (delta_x == 2 || delta_x == -2) && // jumped
            isEnemyPiece(src_piece, curr_board[start_x+delta_x/2][start_y+delta_y/2]) // jumped over a enemy piece
        ) {
            // jump over enemy
            // remove jumped over piece
            removePiece(start_x+delta_x/2, start_y+delta_y/2);

            // move src piece
            return Board::movePiece(start_x, start_y, end_x, end_y);

                // TODO: Double jump
                // tell user they can move again for dpouble jump
                // return MoveReturns::MoveAgain;
        } else {
            return MoveReturns::Invalid;
        }


    } else {
        // invalid move if not going forward diagonally
        cout << "Invalid Move! Diagonally Only" << endl;
        return MoveReturns::Invalid;
    }
}



/********************************************* Helper Functions  *********************************************/

