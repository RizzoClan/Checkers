#ifndef PIECES_H
#define PIECES_H

// Standard Includes
#include <string>
#include <sstream>

// 3rd Party Includes

// Our Includes

class Piece {
    public:
        /************************************************ Constructors ***********************************************/
        //@Arg type: int representing the piece's type
        //@Note: Recommend upper level to map piece types to enum class
        Piece(const int start_x, const int start_y, const int type=0);
        virtual ~Piece();

        /******************************************** Getters and Setters ********************************************/
        const int get_x() const;
        const int get_y() const;
        void set_x(const int new_x);
        void set_y(const int new_y);

    private:
        // position of the piece
        int pos_x, pos_y;

        // containins the piece's type (i.e. pawn, rook, king... or red, black)
        int piece_type;

};

#endif
