#ifndef GAME_HPP
#define GAME_HPP
#include "board.hpp"
#include "piece.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cmath>


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
    int gameLoop();

    void getTime() const {return time;};

    void setDifficulty(int d) { difficulty = d; };
    void setScore(uint16_t s) { score = s; };
    void setTime(float t) { time = t; };
    void changeCurrentPiece() { currentPiece = nextPiece; };

    void changeNextPiece() {
        // Randomly choose a piece shape
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, pieceShapes.size()-1);
        int pieceIndex = dis(gen);

        // Create the piece
        Piece piece;
        piece.setShape(pieceShapes[pieceIndex]);
        nextPiece = piece;
    }

    int moveCurrentPiece(char direction);




};

#endif