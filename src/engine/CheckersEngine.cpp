#include "CheckersEngine.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

/**************************************************** Constructors ***************************************************/
CheckersEngine::CheckersEngine()
    // construct parent
    : Board(
        CheckersConstants::standard_checkers_length,
        CheckersConstants::standard_checkers_height
    )

    // create players (teams are red and white)
    , players({
        CheckersPlayer{BasicTeams::Team1, BasicPieces::Red},
        CheckersPlayer{BasicTeams::Team2, BasicPieces::White}
    })
{

}

CheckersEngine::~CheckersEngine() {
    // stub
}

/********************************************** Board Functions **********************************************/

PieceSelectReturns CheckersEngine::selectPiece() {
    cout << "Enter in (x,y) coordinate of piece to move (space seperated): ";
    int x,y {};
    cin >> x >> y;
    cout << "You entered: (" << x << ',' << y << ')' << endl;

    // stub -- TODO: need to first associate players with colors to say if it is an enemy
    return PieceSelectReturns(SelectCodes::Success, x, y);
}


PieceSelectReturns CheckersEngine::selectMoveDest(const int src_x, const int src_y) {
    const bool printSrc = src_x != -1 && src_y != -1;
    const std::string src_str = createCoordStr(src_x, src_y);
    while(true) {
        // if src is provided, print it
        if (printSrc) {
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
            if (printSrc) {
                cout << "Moving" << src_str << "->" << createCoordStr(x,y) << endl;
            }

            // only way to leave function
            return PieceSelectReturns{SelectCodes::Success, x, y};
        } else {
            cout << "Invalid destination. Please try again." << endl;
        }
    }
}

/************************************** Move Piece Function **************************************/
// wrapper that gets user input for destination
MoveReturns CheckersEngine::movePiece(const int start_x, const int start_y) {
    auto sel_dest = selectMoveDest(start_x, start_y);
    return movePiece(start_x, start_y, sel_dest.x, sel_dest.y);
}

MoveReturns CheckersEngine::movePiece(
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
            return MoveReturns::Success;
        }

        // check if the piece that was just moved can hop again
        else if(move_rtn == MoveReturns::MoveAgain) {
            // can only move again with the same piece that was moved originally
            cout << "You can move again with the same piece - double hop" << endl;

            // update to select newly created piece position to move
            to_move_x = dest_x;
            to_move_y = dest_y;

            // TODO: implement helper to ask for user input about were to try moving...
            const PieceSelectReturns sel_dest {selectMoveDest(to_move_x, to_move_y)};
            dest_x = sel_dest.x;
            dest_y = sel_dest.y;
                
            // go back to top of loop
            // move_rtn = MoveReturns::MoveAgain;
            continue;

        } else if (move_rtn == MoveReturns::Invalid) {
            // error case
            cout << "Invalid Move, try again" << endl;
        } else {
            throw("Unkown MoveReturn Handle");
        }
    }

    // should never reach this point
    throw("Reached unexpected end of move function");
}



/******************************************** Helper Board Functions ******************************************/

MoveReturns CheckersEngine::tryMove(const int start_x, const int start_y, const int end_x, const int end_y) {
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
            cout << "Jumped over enemy piece" << endl;

            // jumped over a enemy piece
            // thus, move + remove jumped over piece
            removePiece(start_x+delta_x/2, start_y+delta_y/2);

            // move src piece
            MoveReturns mv_rtn = Board::movePiece(start_x, start_y, end_x, end_y);

            // check if can attack again at destination
            if (mv_rtn != MoveReturns::Invalid && canAttack(end_x, end_y)) {
                return MoveReturns::MoveAgain;
            } else {
                return mv_rtn;
            }

        } else {
            return MoveReturns::Invalid;
        }

    } else {
        // invalid move if not going forward diagonally
        cout << "Invalid Move! Diagonally Only" << endl;
        return MoveReturns::Invalid;
    }
}

bool CheckersEngine::isJumpable(const int x, const int y, const int slope, const bool is_upward) const {
    // first eliminate invalid slope
    if (abs(slope) != 1) return false;

    /**
     * based on up or down, eliminates some paths 
     * -- upward means dest_y > src_y
     * -- downward means dest_y < src_y
     * Only affects dest_y
     */
    const int vert_scale = is_upward ? 1 : -1;

    // need to check directly adjecent (1) for enemy and (2) for empty
    for (int adj_degree : {1, 2}) {
        const int dest_x = x + slope*adj_degree; // x +/-1 * adj_degree
        const int dest_y = y + vert_scale*adj_degree;
        const Piece& adj_piece = getPiece(dest_x, dest_y);
        if (adj_degree == 1 && !isEnemyPiece(getPiece(x,y), adj_piece)) return false;
        else if (adj_degree == 2 && adj_piece.isEmpty()) return true;
        else if (adj_degree == 2) return false;
    }

    // should have returned by now
    return false;
}

bool CheckersEngine::canAttack(const int src_x, const int src_y) const {
    // to be able to attack, must be have a adj enemy piece with a empty space behind it
    // TODO: have to take direction of allowed travel into consideration eventually
    //      -- considering all 4 directions

    // define temnp struct to make calling function 4 times easier
    struct JumpCombo {
        JumpCombo(const int _slope, const int _is_upward) : slope(_slope), is_upward(_is_upward) {}
        const int slope;
        const bool is_upward;
    };

    // arrange in clockwise order from top-left
    const JumpCombo possible_combos[4] = {
        JumpCombo{-1, true},
        JumpCombo{ 1, true},
        JumpCombo{-1, false},
        JumpCombo{ 1, false}
    };

    for (JumpCombo combo : possible_combos) {
        if(isJumpable(src_x, src_y, combo.slope, combo.is_upward)) return true;
    }

    // if non were jumpable, piece cannot attack
    return false;
}

bool CheckersEngine::isEnemyPiece(const Piece& src, const Piece& to_compare) const {
    // since there are only two types of pieces (binary coloring), can do a simple !=
    return src != to_compare && to_compare != BasicPieces::Empty;
}
