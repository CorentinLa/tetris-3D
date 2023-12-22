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

        void constructPiece(Piece piece, int type) {
            if(type != 0 && type != 1 && type != 2) {
                cout << "Error: type must be 0, 1 or 2" << endl;
                return;
            }
            int x = piece.getX();
            int y = piece.getY();
            int z = piece.getZ();

            vector<Coordinates> shape = piece.getShape();

            for(int i=0; i< shape.size(); i++) {
                boardMat[x+shape[i].x][y+shape[i].y][z+shape[i].z] = type;
            }
        }

        // Put the piece as current piece in the board
        void putPiece(Piece piece) { constructPiece(piece, 1); };
        // Put the piece as placed in the board (previous piece)
        void putPiece(Piece piece) { constructPiece(piece, 2); };
        // Remove the piece from the board
        void destroyCurrentPiece(Piece piece) { constructPiece(piece, 0); };


        // Remove a line from the board : type = 'x' or 'y', index = index of the line, z = z coordinate of the line
        void removeLine(char type, int index, int z) {
            if(type != 'x' && type != 'y') {
                cout << "Error: type must be x, y" << endl;
                return;
            }

            if(type == 'x') {
                for(int i=0; i<depth; i++) {
                    for(int j=z; j<height; j++) {
                        boardMat[index][i][j] = boardMat[index][i][j+1];
                    }
                }
            }
            else if(type == 'y') {
                for(int i=0; i<width; i++) {
                    for(int j=z; j<height; j++) {
                        boardMat[i][index][j] = boardMat[i][index][j+1];
                    }
                }
            }
        }
};

#endif