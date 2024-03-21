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

/**
 * @brief Starts the game loop and manages game features.
 * 
 * @param onGoingGame Pointer to the Game object representing the ongoing game.
 * @return int Returns 0 when the game loop is finished.
 */
int startGame(Game* onGoingGame);

#endif