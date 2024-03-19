#ifndef MAIN_HPP
#define MAIN_HPP

#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include "game.hpp"
#include "board.hpp"
#include "../display/3d/display-game.hpp"
#include "../display/interface/display-menu.hpp"

extern int RUN_GAME;
extern int DISPLAY_GAME;
extern int NEW_GAME;
extern int CLOSE_GAME;
extern int SHOW_MENU;

int startGame(Game* onGoingGame);

#endif