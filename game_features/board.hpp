#ifndef BOARD_HPP
#define BOARD_HPP
#include "piece.hpp"
#include <vector>

using namespace std;
class board
{
    private:
        int width;
        int height;
        int depth;
        int[width][height][depth] board; // 0 = empty, 1 = current piece, 2 = previous pieces

    public:
        board();
        board(int width, int height, int depth):   width(width), height(height), depth(depth) {};
        ~board();

        void setWidth(int width);
        void setHeight(int height);
        void setDepth(int depth);

        int getWidth() const return width;
        int getHeight() const return height;
        int getDepth() const return depth;


        void constructPiece(Piece piece);
};

#endif