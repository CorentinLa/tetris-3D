#include "board.hpp"

int Board::constructPiece(Piece piece) {
    int x = piece.getX();
    int y = piece.getY();
    int z = piece.getZ();

    vector<Coordinates> shape = piece.getShape();
    int putPiece = 0;

    // Check if the piece has room below
    for(int i=0; i< shape.size(); i++) {
        if(boardMat[x+shape[i].x][y+shape[i].y][z+shape[i].z -1] == 2) {
            putPiece = 1;
            break;
        } 
    }


    // If not, put the piece as previous pieces
    if(putPiece == 1) {
        for(int i=0; i< shape.size(); i++) {
        boardMat[x+shape[i].x][y+shape[i].y][z+shape[i].z] = 2;
        }
        return 1;
    }

    // If yes, put the piece as current piece
    else {
        for(int i=0; i< shape.size(); i++) {
        boardMat[x+shape[i].x][y+shape[i].y][z+shape[i].z] = 1;
        }
        return 0;
    }
}