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
#include <chrono>
#include <thread>


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
    Game(int width, int depth, int height): board(width, depth, height), score(0), time(0.0f), difficulty(1) {
        readPiecesShapes();
        changeNextPiece();
        changeCurrentPiece();
        changeNextPiece();
        };
    ~Game() = default;

    int readPiecesShapes();
    int gameLoop();

    float getTime() const {return time;};
    Board getBoard() const {return board;};
    int getDifficulty() const {return difficulty;};
    int getScore() const {return score;};

    void setDifficulty(int d) { difficulty = d; };
    void setScore(uint16_t s) { score = s; };
    void setTime(float t) { time = t; };
    void changeCurrentPiece() { currentPiece = nextPiece; };

    Piece getCurrentPiece() const {return currentPiece;};

    void moveCurrentPiece(char direction) {
        switch(direction) {
        case 'X':
            currentPiece.setX(currentPiece.getX()+1);
            break;
        case 'Y':
            currentPiece.setY(currentPiece.getY()+1);
            break;
        case 'Z':
            currentPiece.setZ(currentPiece.getZ()+1);
            break;
        case 'x':
            currentPiece.setX(currentPiece.getX()-1);
            break;
        case 'y':
            currentPiece.setY(currentPiece.getY()-1);
            break;
        case 'z':
            currentPiece.setZ(currentPiece.getZ()-1);
            break;
        default:
            cout << "Error: direction must be X, Y, Z, x, y or z" << endl;
            break;
    }
    }
    void changeNextPiece() {
        // Randomly choose a piece shape
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, pieceShapes.size()-1);
        int pieceIndex = dis(gen);

        // Create the piece
        Piece piece((int)board.getWidth()/2,(int) board.getDepth()/2,board.getHeight()-3);
        //cout << "Piece" << pieceIndex << " created at " << piece.getX() << " " << piece.getY() << " " << piece.getZ() << endl;
        piece.setShape(pieceShapes[pieceIndex]);

        nextPiece = piece;
    }

    // Code in game.cpp
    
    int currentPieceMovable(char direction) const;
    int currentPieceRotatable(char axe, char sens) const;

    int destroyCurrentPiece() {
        board.constructPiece(currentPiece, 0);
        return 0;
    }

    int constructCurrentPiece() {
        board.constructPiece(currentPiece, 1);
        return 0;
    }

    int rotateCurrentPiece(char axe, char sens) {
        currentPiece.rotate(axe, sens);
        return 0;
    }

};

#endif