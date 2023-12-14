#ifndef BOARD_HPP
#define BOARD_HPP
#include "piece.hpp"
#include <vector>

using namespace std;
class Board
{
    private:
        int width;
        int height;
        int depth;
        int*** boardMat; // 0 = empty, 1 = current piece, 2 = previous pieces

        void initBoardMat() {
            boardMat = new int**[width];
            for(int i=0; i<width; i++) {
                boardMat[i] = new int*[height];
                for(int j=0; j<height; j++) {
                    boardMat[i][j] = new int[depth];
                    for(int k=0; k<depth; k++) {
                        boardMat[i][j][k] = 0;
                    }
                }
            }
        };

    public:
        Board();
        Board(int width, int height, int depth):   width(width), height(height), depth(depth) {initBoardMat();};
        ~Board() {
            // Free memory
            for(int i=0; i<width; i++) {
                for(int j=0; j<height; j++) {
                    delete[] boardMat[i][j];
                }
                delete[] boardMat[i];
            }
            delete[] boardMat;
        };

        int getWidth() const {return width;};
        int getHeight() const {return height;};
        int getDepth() const {return depth;};

        int*** getBoardMat() const {return boardMat;};

        // Code in board.cpp
        int constructPiece(Piece piece);
};

#endif