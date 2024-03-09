#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vlc/vlc.h>
#include "game.hpp"
#include "board.hpp"
#include "../display/3d/display-game.hpp"

int playMusic(char const* location, int volume);

class music {
private:
    char const* location;
    int volume;
    libvlc_instance_t *inst;
    libvlc_media_t *vlc_media;
    libvlc_media_player_t *vlc_player;

public:
    music(char const* location, int volume) : location(location), volume(volume) {
        const char * vlc_args[]= {
            "--file-caching=120000"  // Set the file caching value
        };
        inst = libvlc_new(1, vlc_args);
        playMusic(location);
    }

    void playMusic(char const* location) {
        // Play the music 
        if (vlc_player != NULL) libvlc_media_player_stop(vlc_player);
        vlc_media = libvlc_media_new_path(inst, location);

        vlc_player = libvlc_media_player_new_from_media(vlc_media);
        libvlc_audio_set_volume(vlc_player, volume);
        libvlc_media_player_play(vlc_player); //this line will play the video and audio

    }

    int setVolume(int newVolume) {
        volume = newVolume;
        libvlc_audio_set_volume(vlc_player, volume);
        return 0;
    }

    int isPlaying() {
        return libvlc_media_player_is_playing(vlc_player);
    }

    ~music() {
        libvlc_media_player_stop(vlc_player);
        libvlc_media_player_release(vlc_player);
        libvlc_media_release(vlc_media);
        libvlc_release(inst);
    }
};

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