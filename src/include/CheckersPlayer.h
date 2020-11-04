#ifndef PLAYER_H
#define PLAYER_H

// Standard Includes
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// 3rd Party Includes

// Our Includes
#include "constants.h"

class Player {
    public:
        /************************************************ Constructors ***********************************************/
        Player(const BasicTeams team);

        /******************************************** Getters and Setters ********************************************/
        BasicTeams getTeam() const;
        // returns true for success
        bool setTeam(const BasicTeams new_team);

        /********************************************** Player Functions **********************************************/

    private:
        BasicTeams team;

        /********************************************** Helper Functions **********************************************/
};

#endif
