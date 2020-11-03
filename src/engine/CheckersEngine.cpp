#include "CheckersEngine.h"

using std::cout;
using std::cerr;
using std::endl;

/**************************************************** Constructors ***************************************************/
CheckersEngine::CheckersEngine() 
    : CheckersBoard() // construct parent
{

}


/********************************************** Board Functions **********************************************/

const MoveReturns CheckersEngine::movePiece(
    const int start_x, const int start_y,
    const int end_x, const int end_y
) {

    // loop so that if user needs to double hop or does invalid move, they can redo it
    MoveReturns move_rtn = MoveReturns::Invalid; // start off with invalid
    // need to be able to update values for double jumps - start off with passed values
    int to_move_x = start_x;
    int to_move_y = start_y;
    int dest_x = end_x; 
    int dest_y = end_y; 
    while (move_rtn != MoveReturns::Success) {
        // try to move the piece
        move_rtn = CheckersBoard::movePiece(to_move_x, to_move_y, dest_x, dest_y);
        
        // normal case
        if (move_rtn == MoveReturns::Success) {

            // check if the piece that was just moved can hop again
            if(canAttack(dest_x, dest_y)) {
                // can only move again with the same piece that was moved originally
                cout << double_hop_msg << endl;

                // update to select newly created piece position to move
                to_move_x = dest_x;
                to_move_y = dest_y;

                // TODO: implement helper to ask for user input about were to try moving...
                cout << "IMPLEMENT METHOD TO CHOOSE NEXT DEST- defaulting to 0 0" << endl;
                dest_x = 0; 
                dest_y = 0;

                // go back to top of loop
                continue;

            } else {
                // if no more moves, just return success
                return MoveReturns::Success;
            }

        } else if (move_rtn == MoveReturns::Invalid) {
            // error case
            cout << "Invalid Move, try again" << endl;
        } else if (move_rtn == MoveReturns::MoveAgain) {
            cout << double_hop_msg << endl;
        }
    }
}



/********************************************** Helper Functions *********************************************/
const bool CheckersEngine::canAttack(const int x, const int y) const {
    return true;// stub
}

