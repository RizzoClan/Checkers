#ifndef BOARD_H
#define BOARD_H

class Board {
    public:
        /************************************************ Constructors ***********************************************/
        Board(const int length, const int height);


        /******************************************** Getters and Setters ********************************************/
        void setLength(const int new_length);
        void setHeight(const int new_height);
        const int getLength() const;
        const int getHeight() const;

    private:
        int length; // x
        int height; // y

};

#endif
