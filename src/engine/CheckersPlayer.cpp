#include "CheckersPlayer.h"

using std::cout;
using std::cerr;
using std::endl;

/**************************************************** Constructors ***************************************************/
Player::Player(const BasicTeams _team)
    : team(_team)
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



/********************************************** Player Functions **********************************************/


/********************************************** Helper Functions **********************************************/
