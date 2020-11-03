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
    Success,
    Invalid,
    MoveAgain
};

const std::string double_hop_msg = "You can move again with the same piece - double hop";

#endif
