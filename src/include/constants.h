#ifndef CONSTANTS_H
#define CONSTANTS_H

// standard checkers board length
const int standard_checkers_length {8};
const int standard_checkers_height {8};

/**
 * @Brief: Enum containing basic piece types
 *  (Use BasicPieces::Empty to say no piece is there)
 * @Note: extend the class to give it more types
 * @Problem: Char duplication once try to set the chess pieces.
 */
enum class BasicPieces : char {
    Empty='0',
    Red='R',
    White='W',
    Black='B',
    Pawn,
    Bishop,
    Knight,
    Rook,
    Queen,
    King
};

enum class MoveReturns {
    Success = 0,
    Invalid = -1,
    MoveAgain = 1
};

// generally games have only 1-4 teams/players
enum class BasicTeams {
    Team1,
    Team2,
    Team3,
    Team4,
    // some other types of team qualifications
    Red,
    White,
    Black
};

#endif
