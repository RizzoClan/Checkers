#ifndef PLAYER_H
#define PLAYER_H

// Standard Includes
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// 3rd Party Includes

// Our Includes
#include "constants.h"

class Player {
    public:
        /************************************************ Constructors ***********************************************/
        Player(const BasicPieces team);

        /******************************************** Getters and Setters ********************************************/


        /********************************************** Player Functions **********************************************/

    private:
        const BasicPieces team;

        /********************************************** Helper Functions **********************************************/
};

#endif
