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
        Player(const BasicPieces team);

        /******************************************** Getters and Setters ********************************************/
        BasicPieces getTeam() const;
        // returns true for success
        bool setTeam(const BasicPieces new_team);

        /********************************************** Player Functions **********************************************/

    private:
        BasicPieces team;

        /********************************************** Helper Functions **********************************************/
};

#endif
