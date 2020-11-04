#include "CheckersEngine.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

/**************************************************** Constructors ***************************************************/
CheckersEngine::CheckersEngine() 
    : Board(standard_checkers_length, standard_checkers_height) // construct parent
{

}

CheckersEngine::~CheckersEngine() {
    // stub
}

/********************************************** Board Functions **********************************************/

const PieceSelectReturns CheckersEngine::selectPiece() {
    cout << "Enter in (x,y) coordinate of piece to move (space seperated): ";
    int x,y {};
    cin >> x >> y;
    cout << "You entered: (" << x << ',' << y << ')' << endl;

    // stub -- TODO: need to first associate players with colors to say if it is an enemy
    return PieceSelectReturns(SelectCodes::Success, x, y);
}


const PieceSelectReturns CheckersEngine::selectMoveDest(const int src_x, const int src_y) {
    const std::string src_str = createCoordStr(src_x, src_y);
    while(true) {
        // if src is provided, print it
        if (src_x != -1 && src_y != -1) {
            cout << "Starting from" << src_str << endl <<
                "Enter in (x,y) coordinate of where to move (space seperated): ";
        }

        int x,y {};
        cin >> x >> y;
        cout << "You entered: (" << x << ',' << y << ')' << endl;

        // check if dest is already taken
        const SelectCodes rtn_code = isEmpty(x,y) ? SelectCodes::Success : SelectCodes::CannotMove;

        if (rtn_code == SelectCodes::Success) {
            // print src->dest
            cout << "Moving" << src_str << "->" << createCoordStr(x,y) << endl; 

            // only way to leave function
            return PieceSelectReturns(rtn_code, x, y);
        } else {
            cout << "Invalid destination. Please try again." << endl;
        }
    }
}


const MoveReturns CheckersEngine::movePiece(
    const int start_x, const int start_y,
    const int end_x, const int end_y
) {

    // loop so that if user needs to double hop or does invalid move, they can redo it
    MoveReturns move_rtn = MoveReturns::Invalid; // start off with invalid
    // need to be able to update values for double jumps - start off with passed values
    int to_move_x = start_x;
    int to_move_y = start_y;
    int dest_x = end_x; 
    int dest_y = end_y; 
    while (move_rtn != MoveReturns::Success) {
        // try to move the piece
        move_rtn = tryMove(to_move_x, to_move_y, dest_x, dest_y);
        cout << "Updated Board: " << endl << *this << endl;

        // normal case
        if (move_rtn == MoveReturns::Success) {

            // check if the piece that was just moved can hop again
            if(canAttack(dest_x, dest_y)) {
                // can only move again with the same piece that was moved originally
                cout << double_hop_msg << endl;

                // update to select newly created piece position to move
                to_move_x = dest_x;
                to_move_y = dest_y;

                // TODO: implement helper to ask for user input about were to try moving...
                const PieceSelectReturns sel_dest {selectMoveDest(to_move_x, to_move_y)};
                dest_x = sel_dest.x;
                dest_y = sel_dest.y;
                    
                // go back to top of loop
                continue;

            } else {
                // if no more moves, just return success
                return MoveReturns::Success;
            }

        } else if (move_rtn == MoveReturns::Invalid) {
            // error case
            cout << "Invalid Move, try again" << endl;
        } else if (move_rtn == MoveReturns::MoveAgain) {
            cout << double_hop_msg << endl;
        }
    }
}



/******************************************** Helper Board Functions ******************************************/

const MoveReturns CheckersEngine::tryMove(const int start_x, const int start_y, const int end_x, const int end_y) {
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
            cout << "Moving" << createCoordStr(start_x, start_y) 
                << "->" << createCoordStr(end_x, end_y) << endl;
            return Board::movePiece(start_x, start_y, end_x, end_y);

        } else if (!dest_piece.isEmpty()) {
            cout << "Invalid Move! Moving onto an existing piece" << endl;
            return MoveReturns::Invalid;

        } else if(
            (delta_y == 2 || delta_y == -2) && (delta_x == 2 || delta_x == -2) && // jumped
            isEnemyPiece(src_piece, curr_board[start_x+delta_x/2][start_y+delta_y/2])
        ) {
            // jumped over a enemy piece
            // thus, move + remove jumped over piece
            removePiece(start_x+delta_x/2, start_y+delta_y/2);

            // move src piece
            return Board::movePiece(start_x, start_y, end_x, end_y);

        } else {
            return MoveReturns::Invalid;
        }

    } else {
        // invalid move if not going forward diagonally
        cout << "Invalid Move! Diagonally Only" << endl;
        return MoveReturns::Invalid;
    }
}


const bool CheckersEngine::canAttack(const int x, const int y) const {
    return true;// stub
}

const bool CheckersEngine::isEnemyPiece(const Piece& src, const Piece& to_compare) const {
    // since there are only two types of pieces (binary coloring), can do a simple !=
    return src != to_compare;
}
