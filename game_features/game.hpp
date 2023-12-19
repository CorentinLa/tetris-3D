#ifndef GAME_HPP
#define GAME_HPP
#include "board.hpp"
#include "piece.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>


class Game
{
private:
    Board board;
    uint16_t score;
    float time;
    vector<vector<Coordinates>> pieceShapes;
    Piece currentPiece;
    Piece nextPiece;
    int difficulty;

public:
    Game();
    ~Game();

    int readPiecesShapes();
    void run();
};

#endif