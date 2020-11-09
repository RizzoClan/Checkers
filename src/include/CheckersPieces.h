#ifndef CHECKERS_PIECES_H
#define CHECKERS_PIECES_H

// Standard Includes
#include <string>
#include <sstream>

// 3rd Party Includes

// Our Includes
#include "constants.h"
#include "pieces.h"
#include "SpecialPrints.hpp"

namespace Checkers {

class CheckersPiece : public BaseBoard::Piece {
    public:
        /************************************************ Constructors ***********************************************/
        /**
         * @Arg type: represents the piece's type (defaults to empty)
         * @Note: Recommend upper level to map piece types to enum class
         */
        explicit CheckersPiece(const BaseBoard::BasicPieces type=BaseBoard::BasicPieces::Empty);
        /**
         * @Brief: Copy constructor
         */
        explicit CheckersPiece(const CheckersPiece& piece_obj);
        virtual ~CheckersPiece();

        /******************************************** Getters and Setters ********************************************/
        bool getIsKinged() const;
        bool setIsKinged(bool new_state);

        /********************************************** Helper Functions **********************************************/

        /************************************************* Operators *************************************************/
        /**
         * @Brief: Print out an individual piece
         * @Note: Differs from parent in that it underlines king pieces
         */
        friend std::ostream& operator<<(std::ostream& os, const CheckersPiece& this_piece);

    private:
        // set to true if a piece reaches the other end of the board
        bool isKinged;
};

};

#endif