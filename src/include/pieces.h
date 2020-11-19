#ifndef PIECES_H
#define PIECES_H

// Standard Includes
#include <string>
#include <sstream>

// 3rd Party Includes

// Our Includes
#include "constants.h"

namespace BaseBoard {

class Piece {
    public:
        /************************************************ Constructors ***********************************************/
        /**
         * @Arg type: represents the piece's type (defaults to empty)
         * @Note: Recommend upper level to map piece types to enum class
         */
        explicit Piece(const BasicPieces type=BasicPieces::Empty);
        /**
         * @Brief: Copy constructor
         */
        explicit Piece(const Piece& piece_obj);
        virtual ~Piece();

        /******************************************** Getters and Setters ********************************************/
        BasicPieces getType() const;
        bool setType(const BasicPieces new_type);

        /************************************************* Operators *************************************************/
        bool operator==(const Piece& to_compare) const;
        bool operator!=(const Piece& to_compare) const;
        bool operator!=(const BasicPieces& to_compare) const;
        bool operator==(const BasicPieces& to_compare) const;
        friend std::ostream& operator<<(std::ostream& os, const Piece& this_piece);

        /********************************************** Helper Functions **********************************************/
        bool isEmpty() const;

    private:
        // containins the piece's type (i.e. pawn, rook, king... or red, black)
        // dont set as const because in some games the type can change
        BasicPieces piece_type;

};

} // end of BaseBoard namespace

#endif
