#ifndef PLAYER_H
#define PLAYER_H

// Standard Includes
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// 3rd Party Includes

// Our Includes
#include "board.h"
#include "constants.h"

class CheckersPlayer {
    public:
        /************************************************ Constructors ***********************************************/
        /**
         * @Brief Constructor for player object
         * @Args - team: The player's team id
         * @Args - associated_piece (optional): the piece type to associate the player with
         */
        explicit CheckersPlayer(const BasicTeams team, const BasicPieces associated_piece);
        virtual ~CheckersPlayer();

        /******************************************** Getters and Setters ********************************************/
        BasicTeams getTeam() const;
        // returns true for success
        bool setTeam(const BasicTeams new_team);

        BasicPieces getPieceType() const;
        // true for succes
        bool setPieceType(const BasicPieces new_piece_type);

        bool setPieceCount(const int new_piece_count);
        int getPieceCount() const;

        /********************************************** Player Functions **********************************************/

    private:
        BasicTeams team;
        BasicPieces piece_type;
        int num_pieces; // 0-12 pieces
        bool hasLost;

        /********************************************** Helper Functions **********************************************/
};

#endif
