#ifndef PIECES_H
#define PIECES_H

// Standard Includes
#include <string>
#include <sstream>

// 3rd Party Includes

// Our Includes

// enum for game pieces, can use class to add to the enum
// starts off including some common types of game pieces
// enum class GamePieces {
//     Red,
//     Black,
//     White,
//     Pawn,
//     Bishop,
//     Knight,
//     Rook,
//     Queen,
//     King
// };


class Piece {
    public:
        /************************************************ Constructors ***********************************************/
        Piece(const int start_x, const int start_y, std::string type);

        /******************************************** Getters and Setters ********************************************/
        const int get_x() const;
        const int get_y() const;
        void set_x(const int new_x);
        void set_y(const int new_y);

    private:
        // position of the piece
        int pos_x, pos_y;

        // containins the piece's type (i.e. pawn, rook, king... or red, black)
        std::string piece_type;

};

#endif
