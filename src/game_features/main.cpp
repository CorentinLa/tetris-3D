#include"main.hpp"
using namespace std;

int RUN_GAME = 0;
int DISPLAY_GAME = 0;

// The game will have to lock when it reads the keyboard input

int startGame() {
    Parameters params;
    Game onGoingGame(params);
    music gameMusic("./resources/sounds/classic_tetris.flac", onGoingGame.params.volume);
    // Launch keyboard reading thread
    initGame(&onGoingGame);

    // Launch main loop
    while(onGoingGame.endedGame == 1) {
        if(onGoingGame.getTime() > 10 && !gameMusic.isPlaying()) {
            if (onGoingGame.getTime() > 900) {
                gameMusic.playSound("resources/sounds/highscore.flac");
            } else {
            gameMusic.playSound("resources/sounds/classic_tetris.flac");
            }
        }
        unique_lock<mutex> lock(onGoingGame.mtx);
        onGoingGame.endedGame = onGoingGame.gameLoop();
        lock.unlock();
        Board board = onGoingGame.getBoard();
        int*** boardMat = board.getBoardMat();
        update_game(boardMat, board.getWidth(), board.getDepth(), board.getHeight());
        
        // Wait for next iteration. The time to wait depends on the difficulty and the time spent in the game
        this_thread::sleep_for(chrono::milliseconds(max((int)floor(1000/(onGoingGame.getDifficulty()+onGoingGame.getTime()/300)),200/onGoingGame.getDifficulty())));
        if (onGoingGame.getTime() == 900) {
            gameMusic.playSound("resources/sounds/highscore.flac");
        }
    }

return 0;
}

int main(int argc, char** argv) {
    // Launch the interface
    // thread interfaceThread(&interface);

    //display menu(game_state)

    thread display_menu_Thread(&main_display_menu, argc, argv);
    // Launch the game
    thread gameThread(&startGame);
    thread displayThread(&main_display, argc, argv);

    display_menu_Thread.join();
    displayThread.join();
    gameThread.join();

    return 0;
}