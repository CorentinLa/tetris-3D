/* Main class for the 3D Tetris*/

#include "board.hpp"
#include "piece.hpp"

int startGame(int width, int height, int depth) {
    Board board(width, height, depth);
    Piece piece;
    board.constructPiece(piece);
    return 0;
}


int main(){
    
}