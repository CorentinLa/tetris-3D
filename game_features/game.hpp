#ifndef GAME_HPP
#define GAME_HPP
#include "board.hpp"
#include "piece.hpp"


class Game
{
private:
    Board board;
    uint16_t score;
    float time;
    vector<vector<vector<vector<int>>>> pieces;
    Piece currentPiece;
    Piece nextPiece;
    int difficulty;

public:
    Game();
    ~Game();

    void run();
};

#endif