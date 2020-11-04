#include "CheckersPlayer.h"

using std::cout;
using std::cerr;
using std::endl;

/**************************************************** Constructors ***************************************************/
Player::Player(const BasicTeams _team, const BasicPieces associated_piece)
    : team(_team)
    , piece_type(associated_piece)
    , num_pieces(12) // start off with 12 pieces)
    , hasLost(false)
{

}


/******************************************** Getters and Setters ********************************************/
BasicTeams Player::getTeam() const {
    return team;
}

bool Player::setTeam(const BasicTeams new_team) {
    team = new_team;
    return true;
}

BasicPieces Player::getPieceType() const {
    return piece_type;
}

bool Player::setPieceType(const BasicPieces new_piece_type) {
    piece_type = new_piece_type;
    return true;
}

bool Player::setPieceCount(const int new_piece_count) {
    num_pieces = new_piece_count;

    // if lost all pieces, player has lost
    if (num_pieces <= 0) {
        hasLost = true;
    } else {
        hasLost = false;

    }

    return true;
}

int Player::getPieceCount() const {
    return num_pieces;
}

/********************************************** Player Functions **********************************************/


/********************************************** Helper Functions **********************************************/
