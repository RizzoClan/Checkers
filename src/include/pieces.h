#ifndef PIECES_H
#define PIECES_H

// Standard Includes
#include <string>
#include <sstream>

// 3rd Party Includes

// Our Includes
#include "constants.h"

class Piece {
    public:
        /************************************************ Constructors ***********************************************/
        /**
         * @Arg type: represents the piece's type (defaults to empty)
         * @Note: Recommend upper level to map piece types to enum class
         */
        explicit Piece(const BasicPieces type=BasicPieces::Empty);
        explicit Piece(const int start_x, const int start_y, const BasicPieces type=BasicPieces::Empty);
        virtual ~Piece();

        /******************************************** Getters and Setters ********************************************/
        const int get_x() const;
        const int get_y() const;
        const BasicPieces get_type() const;
        void set_x(const int new_x);
        void set_y(const int new_y);
        void set_type(const BasicPieces new_type);

    private:
        // position of the piece
        int pos_x, pos_y;

        // containins the piece's type (i.e. pawn, rook, king... or red, black)
        // dont set as const because in some games the type can change
        BasicPieces piece_type;

};

#endif
