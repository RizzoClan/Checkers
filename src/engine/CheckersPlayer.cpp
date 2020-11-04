#include "CheckersPlayer.h"

using std::cout;
using std::cerr;
using std::endl;

/**************************************************** Constructors ***************************************************/
Player::Player(const BasicTeams _team, const BasicPieces associated_team)
    : team(_team)
    , piece_type(associated_team)
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


/********************************************** Player Functions **********************************************/


/********************************************** Helper Functions **********************************************/
