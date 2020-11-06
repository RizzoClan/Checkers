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

namespace Checkers {

class CheckersPlayer {
    public:
        /************************************************ Constructors ***********************************************/
        /**
         * @Brief Constructor for player object
         * @Args - team: The player's team id
         * @Args - associated_piece: the piece type to associate the player with (Red or White)
         */
        explicit CheckersPlayer(const BaseBoard::BasicTeams team, 
            const BaseBoard::BasicPieces associated_piece);
        virtual ~CheckersPlayer();

        /******************************************** Getters and Setters ********************************************/
        // returns Team1 or Team2
        BaseBoard::BasicTeams getTeam() const;
        // returns true for success
        bool setTeam(const BaseBoard::BasicTeams new_team);

        BaseBoard::BasicPieces getPieceType() const;
        // true for succes
        bool setPieceType(const BaseBoard::BasicPieces new_piece_type);

        // set piece count back to max
        bool resetPieceCount();
        bool setPieceCount(const int new_piece_count);
        int getPieceCount() const;

        /********************************************** Player Functions **********************************************/

    private:
        BaseBoard::BasicTeams team;
        BaseBoard::BasicPieces piece_type;
        int num_pieces; // 0-12 pieces
        bool hasLost;

        /********************************************** Helper Functions **********************************************/
};

} // end of Checkers namespace
#endif
