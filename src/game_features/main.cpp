#include"main.hpp"
using namespace std;

// The game will have to lock when it reads the keyboard input

int startGame() {
    Parameters params;
    Game onGoingGame(params);
    // music gameMusic("resources/sounds/classic_tetris.flac", onGoingGame.params.volume);
    // Launch keyboard reading thread
    initGame(&onGoingGame);

    // Launch main loop
    int gameEnded = 1;
    while(gameEnded) {
        // if(onGoingGame.getTime() > 10 && !gameMusic.isPlaying()) {
        //     if (onGoingGame.getTime() > 900) {
        //         gameMusic.playSound("resources/sounds/highscore.flac");
        //     } else {
        //     gameMusic.playSound("resources/sounds/classic_tetris.flac");
        //     }
        // }
        gameEnded = onGoingGame.gameLoop();
        Board board = onGoingGame.getBoard();
        int*** boardMat = board.getBoardMat();
        update_game(boardMat, board.getWidth(), board.getDepth(), board.getHeight());
        
        // Wait for next iteration. The time to wait depends on the difficulty and the time spent in the game
        this_thread::sleep_for(chrono::milliseconds(max((int)floor(1000/(onGoingGame.getDifficulty()+onGoingGame.getTime()/300)),200/onGoingGame.getDifficulty())));
        // if (onGoingGame.getTime() == 900) {
        //     gameMusic.playSound("resources/sounds/highscore.flac");
        // }
    }

return 0;
}


int main(int argc, char** argv) {
    // Launch the interface
    // thread interfaceThread(&interface);


    // Launch the game
    thread gameThread(&startGame);
    thread displayThread(&main_display, argc, argv);
    
    displayThread.join();
    gameThread.join();

    return 0;
}