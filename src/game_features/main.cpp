#include"main.hpp"
using namespace std;


int startGame(Game* onGoingGame) {
    // music gameMusic("./resources/sounds/classic_tetris.flac", onGoingGame.params.volume);
    initGame(onGoingGame);

    // Launch main loop
    while(onGoingGame->endedGame == 1) {
        if (onGoingGame->pausedGame) {
            // gameMusic.StopSound();
            while (onGoingGame->pausedGame) {
                this_thread::sleep_for(chrono::milliseconds(100));
            }
            // gameMusic.playSound("resources/sounds/classic_tetris.flac");
        }

        // if(onGoingGame->getTime() > 10 && !gameMusic.isPlaying()) {
        //     if (onGoingGame->getTime() > 900) {
        //         gameMusic.playSound("resources/sounds/highscore.flac");
        //     } else {
        //     gameMusic.playSound("resources/sounds/classic_tetris.flac");
        //     }
        // }
        unique_lock<mutex> lock(onGoingGame->mtx);
        if (onGoingGame->endedGame) onGoingGame->endedGame = onGoingGame->gameLoop();
        lock.unlock();
        Board board = onGoingGame->getBoard();
        int*** boardMat = board.getBoardMat();
        update_game(boardMat, board.getWidth(), board.getDepth(), board.getHeight());
        
        // Wait for next iteration. The time to wait depends on the difficulty and the time spent in the game
        this_thread::sleep_for(chrono::milliseconds(max((int)floor(1000/(onGoingGame->getDifficulty()+onGoingGame->getTime()/300)),200/onGoingGame->getDifficulty())));
        // if (onGoingGame->getTime() == 900) {
        //     gameMusic.playSound("resources/sounds/highscore.flac");
        // }
        }
    return 0;
}

int main(int argc, char** argv) {

    // Launch the game
    thread displayMenuThread(&main_display_menu);

    displayMenuThread.join();
    
    cout << "here" << endl;
    return 0;
}