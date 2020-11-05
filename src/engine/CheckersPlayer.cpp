#include "CheckersPlayer.h"

using std::cout;
using std::cerr;
using std::endl;

/**************************************************** Constructors ***************************************************/
CheckersPlayer::CheckersPlayer(const BasicTeams _team, const BasicPieces associated_piece)
    : team(_team)
    , piece_type(associated_piece)
    , num_pieces(CheckersConstants::max_player_pieces) // start off with 12 pieces
    , hasLost(false)
{

}

CheckersPlayer::~CheckersPlayer() {
    //stub
}


/******************************************** Getters and Setters ********************************************/
BasicTeams CheckersPlayer::getTeam() const {
    return team;
}

bool CheckersPlayer::setTeam(const BasicTeams new_team) {
    team = new_team;
    return true;
}

BasicPieces CheckersPlayer::getPieceType() const {
    return piece_type;
}

bool CheckersPlayer::setPieceType(const BasicPieces new_piece_type) {
    piece_type = new_piece_type;
    return true;
}

bool CheckersPlayer::resetPieceCount() {
    return setPieceCount(CheckersConstants::max_player_pieces);
}


bool CheckersPlayer::setPieceCount(const int new_piece_count) {
    num_pieces = new_piece_count;

    // if lost all pieces, player has lost
    if (num_pieces <= 0) {
        hasLost = true;
    } else {
        hasLost = false;

    }

    return true;
}

int CheckersPlayer::getPieceCount() const {
    return num_pieces;
}

/********************************************** Player Functions **********************************************/


/********************************************** Helper Functions **********************************************/