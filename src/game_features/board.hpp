#ifndef BOARD_HPP
#define BOARD_HPP
#include "piece.hpp"
#include <vector>

using namespace std;
class Board
{
    private:
        int width;
        int depth;
        int height;
        int*** boardMat; // 0 = empty, 1 = current piece, 2 = previous pieces

        void initBoardMat() {
            boardMat = new int**[width];
            for(int i=0; i<width; i++) {
                boardMat[i] = new int*[depth];
                for(int j=0; j<depth; j++) {
                    boardMat[i][j] = new int[height];
                    for(int k=0; k<height; k++) {
                        // fill the ground with 3
                        if(k == 0) {
                            boardMat[i][j][k] = 3;
                        }
                        else boardMat[i][j][k] = 0;
                    }
                }
            }
        };

    public:
        Board();
        Board(int width, int depth, int height):    width(width), depth(depth),height(height) {initBoardMat();};
        ~Board() {
            // Free memory
            //cout << boardMat << endl;
            //cout << "Deleting board" << endl;
            for(int i=0; i<width; i++) {
                //cout << "Deleting boardMat[" << i << "]" << endl;
                for(int j=0; j<depth; j++) {
                    delete[] boardMat[i][j];
                }
                delete[] boardMat[i];
            }
            delete[] boardMat;
        };

        // Copy constructor
        Board(const Board& oldBoard) {
            width = oldBoard.width;
            depth = oldBoard.depth;
            height = oldBoard.height;
            initBoardMat();
            for(int i=0; i<width; i++) {
                for(int j=0; j<depth; j++) {
                    for(int k=0; k<height; k++) {
                        boardMat[i][j][k] = oldBoard.boardMat[i][j][k];
                    }
                }
            }
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
                // To permit to construct a piece even tho it would go out of the space.
                if(!(x+shape[i].x >= width || y+shape[i].y >= depth || z+shape[i].z > height)) boardMat[x+shape[i].x][y+shape[i].y][z+shape[i].z] = type;
                // cout << "x = " << x+shape[i].x << " y = " << y+shape[i].y << " z = " << z+shape[i].z << endl;
            }
        }



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