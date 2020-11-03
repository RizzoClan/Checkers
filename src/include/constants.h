#ifndef CONSTANTS_H
#define CONSTANTS_H

// standard checkers board length
const int standard_checkers_length {8};
const int standard_checkers_height {8};

/**
 * @Brief: Enum containing basic piece types
 *  (Use BasicPieces::Empty to say no piece is there)
 * @Note: extend the class to give it more types
 */
enum class BasicPieces {
    Empty,
    Red,
    White,
    Black,
    Pawn,
    Bishop,
    Knight,
    Rook,
    Queen,
    King
};


#endif
