#include "CheckersPlayer.h"

using std::cout;
using std::cerr;
using std::endl;

/**************************************************** Constructors ***************************************************/
Player::Player(const BasicPieces _team)
    : team(_team)
{

}


/******************************************** Getters and Setters ********************************************/
BasicPieces Player::getTeam() const {
    return team;
}

bool Player::setTeam(const BasicPieces new_team) {
    team = new_team;
    return true;
}



/********************************************** Player Functions **********************************************/


/********************************************** Helper Functions **********************************************/
