#include "CheckersEngine.h"

// common std namespace elements
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

// our common namespace elements
using BaseBoard::BasicPieces;
using BaseBoard::BasicTeams;
using BaseBoard::MoveReturns;

namespace Checkers {

/**************************************************** Constructors ***************************************************/
CheckersEngine::CheckersEngine()
    // construct parent
    : CheckersBoard()

    // create players (teams are red and white)
    // map the different colors to their corresponding elements in the array
    , piece_to_player({
        {BasicPieces::Red,  CheckersPlayer{BasicTeams::Team1, BasicPieces::Red}},
        {BasicPieces::White, CheckersPlayer{BasicTeams::Team2, BasicPieces::White}}
    })
{
    if(!resetBoard()) {
        cerr << "Error creating board" << endl;
        return;
    }
}

CheckersEngine::~CheckersEngine() {
    // stub
}

/********************************************** Board Functions **********************************************/

BaseBoard::BasicTeams CheckersEngine::play() {
    bool isStillPlaying = true;
    CheckersPlayer& red_player {piece_to_player.at(BasicPieces::Red)};
    CheckersPlayer& white_player {piece_to_player.at(BasicPieces::White)};

    while (isStillPlaying) {
        // start with darker peice (red)
        cout << "Red Player's Move - ";
        const PieceSelectReturns red_to_move {selectPiece(red_player.getPieceType())};
        movePiece(red_to_move.x, red_to_move.y);
        if (red_player.getPieceCount() == 0) return white_player.getTeam();

        // next white piece goes
        cout << "White Player's Move - ";
        const PieceSelectReturns white_to_move {selectPiece(white_player.getPieceType())};
        movePiece(white_to_move.x, white_to_move.y);
        if (white_player.getPieceCount() == 0) return white_player.getTeam();
    }

    // if reach this point, it is a draw
    return BaseBoard::BasicTeams::None;
}

// piece_type default to empty
PieceSelectReturns CheckersEngine::selectPiece(const BaseBoard::BasicPieces piece_type) {
    while (true) {
        // fix for entering in a string & causing infinite loop
        cout << "Enter in (x,y) coordinate of piece to move (space seperated): ";
        char x_buf, y_buf;
        cin >> x_buf >> y_buf;
        const int x {static_cast<int>(x_buf)};
        const int y {static_cast<int>(y_buf)};
        cout << "You entered: (" << x << ',' << y << ')' << endl;


        if (piece_type == BaseBoard::BasicPieces::Empty || getPiece(x,y).getType() == piece_type) {
            return PieceSelectReturns(SelectCodes::Success, x, y);
        } else {
            cerr << "Invalid piece selected, try again" << endl;
        }
    }
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
        cout << "You entered: " << createCoordStr(x, y) << endl;

        // check if dest is already taken
        // and check if is valid move
        const SelectCodes rtn_code = isEmpty(x,y) && isValidMovePath(src_x, src_y, x, y) ?
            SelectCodes::Success : SelectCodes::CannotMove;

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

bool CheckersEngine::initPlayerOnBoard(const CheckersPlayer& player) {
    /**
     * (see https://ctycms.com/mn-rochester/docs/checkers-instructions.pdf)
     * Starting Board:
     *      Use Top & Bot 3 Rows (2 middle rows are empty)
     *      Red (Bot) vs White (Top)
     *      Pieces can only be placed on darkspaces (odd)
     *      i.e.: 
     *          Top: (1,0), (3,0), (0,1), (2,1), (1,2), ...
     *          Bot: (0,5), (1,6), (0,7), ...
     *          Mid: Y = 3 or 4
     */

    // to make repeatable, place pieces left->right from top->bot
    const BasicPieces piece_type = player.getPieceType();
    if (piece_type != BasicPieces::Red && piece_type != BasicPieces::White) {
        throw("Unexpected piece type for Checkers!");
    }

    // determine offsets based on color 
    // (red first piece in row y=5)
    // white pieces cannot be placed passed middle
    const int y_offset = piece_type == BasicPieces::Red ? 5 : 0;
    const int y_max    = piece_type == BasicPieces::Red ? getHeight() : 2; // inclusive for red 

    // go row by row (keep y constant)
    for (int y = y_offset; y < getHeight() && y <= y_max; y++) {
        for (int x = 0; x < getLength(); x++) {

            // has to be odd and not in row 3 or 4
            if ( ((x+y) % 2 == 1) && (y != 3 && y != 4) ) {

                // if fail to insert piece, failed and return
                if(!insertPiece(x, y, piece_type)) {
                    return false;
                }

            }
        }
    }

    return true;
}


bool CheckersEngine::resetBoard() {
    for (auto& piece_player_pair : piece_to_player) {
        CheckersPlayer& player_to_init = piece_player_pair.second;

        if(!initPlayerOnBoard(player_to_init)) {
            // if failed placing on board, print it and reset/wipe board
            cerr << "Failed inserting piece..." << endl << *this << endl;
            cerr << "Resetting board to scratch" << endl;
            Board::resetBoard();
            return false;
        }

        // reset counters of player
        player_to_init.resetPieceCount();
    }

    return true;
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

    const BasicPieces& src_type = getPiece(to_move_x, to_move_y).getType();
    const CheckersPlayer& src_player = piece_to_player.at(src_type);
    if (!isValidMoveDir(
        src_player, BaseBoard::BoardCoord{to_move_x, to_move_y},
        BaseBoard::BoardCoord{dest_x, dest_y}
    )) {
        return MoveReturns::WrongDirection;
    }

    /**
     * https://en.wikipedia.org/wiki/Ultra_checkers#Upgrades
     * only king a piece at end of successive movements
     * keep bool that gets set true if needed and king at end of loop
     */
    bool should_king_piece = false;
    while (move_rtn != MoveReturns::Success) {
        // try to move the piece
        move_rtn = tryMove(to_move_x, to_move_y, dest_x, dest_y);
        cout << "Updated Board: " << endl << *this << endl;

        //  determine if should king the piece (maintain past values with or)
        should_king_piece |= shouldKing(dest_x, dest_y);

        // normal case -- only triggered at end of sequential jumps
        if (move_rtn == MoveReturns::Success) {
            if (should_king_piece) {
                cout << "Kinged " << BaseBoard::BoardCoord{dest_x,dest_y} 
                    << " because it reached other end of board during turn" << endl;
                kingPiece(dest_x, dest_y);
                // print updated board with king piece shown
                cout << "Updated Board with King Piece: " << endl << *this << endl;
            }
            return MoveReturns::Success;
        }

        // check if the piece that was just moved can hop again
        else if(move_rtn == MoveReturns::MoveAgain) {
            // can only move again with the same piece that was moved originally
            cout << "You can move again with the same piece - double hop" << endl;

            // update to select newly created piece position to move
            to_move_x = dest_x;
            to_move_y = dest_y;

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
    // prevent divide by zero by setting to zero so diag_move is false 
    const float move_slope =  delta_x != 0 ?  delta_y / delta_x : 0;
    const bool diag_move = (move_slope == -1 || move_slope == 1);

    if (diag_move) {
        //  get relative pieces
        auto& curr_board = getBoard();
        CheckersPiece& src_piece = curr_board[start_x][start_y];
        CheckersPiece& dest_piece = curr_board[end_x][end_y];

        //  check if there is a piece in dest or jumping over an enemy
        if (dest_piece.isEmpty() && (delta_y == 1 || delta_y == -1)) {
            // normal move into empty space
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
            const BaseBoard::BoardCoord to_remove{start_x+delta_x/2, start_y+delta_y/2};
            cout << "Removing jumped over enemy piece: " << to_remove << endl;
            const BaseBoard::BasicPieces removed_type {removePiece(to_remove)};
            if(removed_type != BaseBoard::BasicPieces::Empty) {
                // successfully removed (decrement piece count)
                CheckersPlayer& to_decr {piece_to_player.at(removed_type)};
                if (!to_decr.setPieceCount(to_decr.getPieceCount()-1)) {
                    // count--
                    cerr << "Failed to decrement piece counter" << endl;
                }
            } else {
                cerr << "Failed to remove the piece" << endl;
            }

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
        // prevent out of bounds error
        if (isOutOfBounds(dest_x, dest_y)) continue;

        const CheckersPiece& adj_piece = getPiece(dest_x, dest_y);
        if (adj_degree == 1 && !isEnemyPiece(getPiece(x,y), adj_piece)) return false;
        else if (adj_degree == 2 && adj_piece.isEmpty()) return true;
        else if (adj_degree == 2) return false;
    }

    // should have returned by now
    return false;
}

bool CheckersEngine::canAttack(const int src_x, const int src_y) const {
    // to be able to attack, must be have a adj enemy piece with a empty space behind it

    // define temnp struct to make calling function 4 times easier
    struct JumpCombo {
        // constructor symolizing invalid jump direction
        JumpCombo(const bool is_valid_jump) :
            slope(0), is_upward(false), is_valid(is_valid_jump) {}

        JumpCombo(const int _slope, const int _is_upward) : 
            slope(_slope), is_upward(_is_upward), is_valid(true) {}

        const int slope;
        const bool is_upward;
        const bool is_valid; // false if not valid jump direction based on piece
    };

    const CheckersPiece& src_piece {getPiece(src_x, src_y)};

    // arrange in clockwise order from top-left
    // define some combos as invalid (i.e. a red-pawn cannot go downward)
    // kings can go any diagonal direction
    const JumpCombo possible_combos[4] = {
        canMoveAny(src_piece) || canMoveUp(src_piece)   ? JumpCombo{-1, true}   : JumpCombo{false},
        canMoveAny(src_piece) || canMoveDown(src_piece) ? JumpCombo{ 1, true}   : JumpCombo{false},
        canMoveAny(src_piece) || canMoveUp(src_piece)   ? JumpCombo{-1, false}  : JumpCombo{false},
        canMoveAny(src_piece) || canMoveDown(src_piece) ? JumpCombo{ 1, false}  : JumpCombo{false},
    };

    for (JumpCombo combo : possible_combos) {
        if(combo.is_valid && isJumpable(src_x, src_y, combo.slope, combo.is_upward)) return true;
    }

    // if non were jumpable, piece cannot attack
    return false;
}

bool CheckersEngine::isEnemyPiece(const CheckersPiece& src, const CheckersPiece& to_compare) const {
    // since there are only two types of pieces (binary coloring), can do a simple !=
    return src != to_compare && to_compare != BasicPieces::Empty;
}

bool CheckersEngine::isValidMoveDir(
    const CheckersPlayer& player,
    const BaseBoard::BoardCoord src,
    const BaseBoard::BoardCoord dest
) const {
    /**
     * Red pieces can only move up (unless kinged)
     * White pieces can only move down (unless kinged)
     * y = [0-7] where 0 is top -- a move down has positive delta_yand vice versa
     * if can_move_up/down but not both: automatically return false if moving opposite direction
     */
    const int delta_y = (dest-src).y;
    const bool can_move_up =    player.getPieceType() == BasicPieces::Red && canMoveUp(getPiece(src));
    const bool can_move_down =  player.getPieceType() == BasicPieces::White  && canMoveDown(getPiece(src));
    const bool can_move_any =   canMoveAny(getPiece(src)); // only true for kings

    // check all conditions vs actuality
    if (can_move_any) return true;
    else if ((can_move_up && delta_y > 0) || (can_move_down && delta_y < 0)) return false;
    else return true;
}

bool CheckersEngine::isValidMovePath(
    const int src_x, const int src_y, const int dest_x, const int dest_y
) const {
    return isValidMovePath(
        BaseBoard::BoardCoord{src_x, src_y}, BaseBoard::BoardCoord{dest_x, dest_y});
}

bool CheckersEngine::isValidMovePath(
    const BaseBoard::BoardCoord src, const BaseBoard::BoardCoord dest
) const {
    const BaseBoard::BoardCoord deltas {dest - src};
    return     abs(deltas.x) != 0
            && abs(deltas.y) != 0
            && abs(deltas.y/deltas.x) == 1 // only perform division when not dividing by zero
            ? true : false;
} // end of Checkers namespace

bool CheckersEngine::shouldKing(const int x, const int y) const {
    // if reds reach top or whites reach bot
    const BasicPieces piece_type = getPiece(x,y).getType();
    return (piece_type == BasicPieces::Red && y == 0) || 
        (piece_type == BasicPieces::White && y == getHeight())
        ? true : false;
}

bool CheckersEngine::kingPiece(const int x, const int y) {
    return getPiece(x,y).setIsKinged(true);
}

/*
    const bool can_move_down = player.getPieceType() == BasicPieces::White;
    const bool can_move_up = player.getPieceType() == BasicPieces::Red;
    const bool can_move_any = getPiece(src).getIsKinged(); // only true for kings
*/

// helper function to determine which direction a piece can move
bool CheckersEngine::canMoveDown(const CheckersPiece& piece_obj) const {
    return piece_obj.getType() == BasicPieces::White || piece_obj.getIsKinged();
}

bool CheckersEngine::canMoveUp(const CheckersPiece& piece_obj) const {
    return piece_obj.getType() == BasicPieces::Red || piece_obj.getIsKinged();

}

bool CheckersEngine::canMoveAny(const CheckersPiece& piece_obj) const {
    return piece_obj.getIsKinged();
}



}
