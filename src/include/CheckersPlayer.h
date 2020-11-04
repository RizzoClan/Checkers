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
        /**
         * @Brief Constructor for player object
         * @Args - team: The player's team id
         * @Args - associated_team (optional): the piece type to associate the player with
         */
        explicit Player(const BasicTeams team, const BasicPieces associated_team);

        /******************************************** Getters and Setters ********************************************/
        BasicTeams getTeam() const;
        // returns true for success
        bool setTeam(const BasicTeams new_team);

        BasicPieces getPieceType() const;
        // true for succes
        bool setPieceType(const BasicPieces new_piece_type);

        /********************************************** Player Functions **********************************************/

    private:
        BasicTeams team;
        BasicPieces piece_type;

        /********************************************** Helper Functions **********************************************/
};

#endif
