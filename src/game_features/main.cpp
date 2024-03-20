#include "main.hpp"
using namespace std;

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
        onGoingGame->mtx.lock();
        if (onGoingGame->endedGame)
            onGoingGame->endedGame = onGoingGame->gameLoop();
        onGoingGame->mtx.unlock();
        Board board = onGoingGame->getBoard();
        int ***boardMat = board.getBoardMat();
        update_game(boardMat, board.getWidth(), board.getDepth(), board.getHeight());

        // Wait for next iteration. The time to wait depends on the difficulty and the time spent in the game
        this_thread::sleep_for(chrono::milliseconds(max((int)floor(1000 / (onGoingGame->getDifficulty() + onGoingGame->getTime() / 300)), 200 / onGoingGame->getDifficulty())));
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