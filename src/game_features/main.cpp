#include "main.hpp"
using namespace std;

/**
 * @brief Starts the game loop and manages game features.
 * 
 * @param onGoingGame Pointer to the Game object representing the ongoing game.
 * @return int Returns 0 when the game loop is finished.
 */
int startGame(Game *onGoingGame)
{
    music gameMusic("./resources/sounds/classic_tetris.flac", onGoingGame->params.volume);
    initGame(onGoingGame);

    // Launch main loop
    while (onGoingGame->endedGame == 1)
    {
        if (onGoingGame->pausedGame)
        {
            gameMusic.pause();
            while (onGoingGame->pausedGame)
            {
                this_thread::sleep_for(chrono::milliseconds(100));
            }
            gameMusic.setVolume(onGoingGame->params.volume);
            gameMusic.resume();
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        // Nécessaire de laisser du temps à la musique de se lancer
        if (onGoingGame->getTime() > 10 && !gameMusic.isPlaying() && (onGoingGame->getTime() < 300 || onGoingGame->getTime() >= 305))
        {
            if (onGoingGame->getTime() > 300)
            {
                gameMusic.playSound("./resources/sounds/highscore.flac");
            }
            else
            {
                gameMusic.playSound("./resources/sounds/classic_tetris.flac");
            }
        }
        // Game loop : update the game state
        onGoingGame->mtx.lock();
        if (onGoingGame->endedGame)
            onGoingGame->endedGame = onGoingGame->gameLoop();
        onGoingGame->mtx.unlock();

        // Update display board
        Board board = onGoingGame->getBoard();
        int ***boardMat = board.getBoardMat();
        update_game(boardMat, board.getWidth(), board.getDepth(), board.getHeight());

        // Wait for next iteration. The time to wait depends on the difficulty and the time spent in the game
        this_thread::sleep_for(chrono::milliseconds(max((int)floor(1000 / (onGoingGame->getDifficulty() + onGoingGame->getTime() / 300)), 200 / onGoingGame->getDifficulty())));
        
        // When a highscore is reached, play a different music
        if (onGoingGame->getTime() == 300)
        {
            gameMusic.playSound("./resources/sounds/highscore.flac");
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    // Launch the game
    thread displayMenuThread(&main_display_menu);

    displayMenuThread.join();

    return 0;
}