#include "board.hpp"

int Board::constructPiece(Piece piece) {
    int x = piece.getX();
    int y = piece.getY();
    int z = piece.getZ();

    vector<vector<vector<int>>> shape = piece.getShape();
    int putPiece = 0;

    // Check if the piece has room below
    for(int i=0; i<shape.size(); i++) {
        for(int j=0; j<shape[i].size(); j++) {
            for(int k=0; k<shape[i][j].size(); k++) {
                if(shape[i][j][k] == 1 && boardMat[x+i][y+j][z+k-1] == 2) {
                    putPiece = 1;
                    break;
                }
            }
        }
    }

    // If not, put the piece as previous pieces
    if(putPiece == 1) {
        for(int i=0; i<shape.size(); i++) {
            for(int j=0; j<shape[i].size(); j++) {
                for(int k=0; k<shape[i][j].size(); k++) {
                    if(shape[i][j][k] == 1) {
                        boardMat[x+i][y+j][z+k] = 2;
                    }
                }
            }
        }
        return 1;
    }

    // If yes, put the piece as current piece
    else {
        for(int i=0; i<shape.size(); i++) {
            for(int j=0; j<shape[i].size(); j++) {
                for(int k=0; k<shape[i][j].size(); k++) {
                    if(shape[i][j][k] == 1) {
                        boardMat[x+i][y+j][z+k] = 1;
                    }
                }
            }
        }
        return 0;
    }
}