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
// #include <vlc/vlc.h>

// int playMusic(char const* location, int volume);

// class music {
// private:
//     char const* location;
//     int volume;
//     libvlc_instance_t *inst;
//     libvlc_media_t *vlc_media;
//     libvlc_media_player_t *vlc_player;

// public:
//     music(char const* location, int volume) : location(location), volume(volume), vlc_player(NULL) {
//         const char * vlc_args[]= {
//             "--file-caching=120000"  // Set the file caching value
//         };
//         inst = libvlc_new(1, vlc_args);
//         playSound(location);
//     }

//     void playSound(char const* location) {
//         // Play the music 
//         if (vlc_player != NULL) libvlc_media_player_stop(vlc_player);
//         vlc_media = libvlc_media_new_path(inst, location);
//         vlc_player = libvlc_media_player_new_from_media(vlc_media);
//         libvlc_audio_set_volume(vlc_player, volume);
//         libvlc_media_player_play(vlc_player); //this line will play the video and audio

//     }

//     int setVolume(int newVolume) {
//         volume = newVolume;
//         libvlc_audio_set_volume(vlc_player, volume);
//         return 0;
//     }

//     int isPlaying() {
//         return libvlc_media_player_is_playing(vlc_player);
//     }

//     ~music() {
//         libvlc_media_player_release(vlc_player);
//         libvlc_media_release(vlc_media);
//         libvlc_release(inst);
//     }
// };

class Parameters {
public:
    int difficulty;
    int width;
    int depth;
    int height;
    int volume;

    Parameters() {
        readParameters();
    }

    void readParameters() {
        // Read parameters from a file
        std::fstream configFile;
        configFile.open("./resources/data/config.cfg");
        if (!configFile) {
            std::cout << "Error: cannot open config.cfg" << std::endl;
        } else {
            std::string line;
            while (std::getline(configFile, line)) {
                if (line.find("difficulty=") != std::string::npos) {
                    sscanf(line.c_str(), "difficulty=%d", &difficulty);
                } else if (line.find("width=") != std::string::npos) {
                    sscanf(line.c_str(), "width=%d", &width);
                } else if (line.find("depth=") != std::string::npos) {
                    sscanf(line.c_str(), "depth=%d", &depth);
                } else if (line.find("height=") != std::string::npos) {
                    sscanf(line.c_str(), "height=%d", &height);
                } else if (line.find("volume=") != std::string::npos) {
                    sscanf(line.c_str(), "volume=%d", &volume);
                }
            }
            configFile.close();
        }
    }
};

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
    Parameters params;

    Game(Parameters params) : params(params), board(params.width, params.depth, params.height), score(0), time(0), difficulty(params.difficulty){
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
        // if(direction != 'z') {
        //     std::thread([this] {
        //         music sound("resources/sounds/move.mp3", max(params.volume, 0));
        //         this_thread::sleep_for(chrono::milliseconds(200));
        //     }).detach();
        // }
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
        // std::thread([this] {
        //         music sound("resources/sounds/move.mp3", max(params.volume, 0));
        //         this_thread::sleep_for(chrono::milliseconds(200));
        //     }).detach();
        // currentPiece.rotate(axe, sens);
        return 0;
    }

};


#endif