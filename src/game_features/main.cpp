#include"main.hpp"
using namespace std;

int RUN_GAME = 0;
int DISPLAY_GAME = 0;
int NEW_GAME = 0;
int CLOSE_GAME = 0;

// The game will have to lock when it reads the keyboard input

int startGame() {
    Parameters params;
    Game onGoingGame(params);
    music gameMusic("./resources/sounds/classic_tetris.flac", onGoingGame.params.volume);
    // Launch keyboard reading thread
    initGame(&onGoingGame);

    // Launch main loop
    while(onGoingGame.endedGame == 1) {
        if (NEW_GAME) {
            //premier état possible : on vient de lancer une nouvelle partie donc on reset onGoingGame et on passe RUN_GAME à 1 pour lancer la nouvelle partie
                NEW_GAME = 0;
                RUN_GAME = 1;
                DISPLAY_GAME = 1;
                onGoingGame.reset();
            }
        if (RUN_GAME) {
            //deuxième état possible : pas de nouvelle partie, on lance la partie si elle n'est pas déjà lancée/on actualise le jeu si la partie est déjà lancée
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
        else {
            //troisième état possible : pas de partie lancée et pas de lancement de nouvelle partie demandée, càd on est dans le menu
            gameMusic.StopSound();
            if (CLOSE_GAME) {
                return 0;
            }
        }
    }
    return 0;
}

int main(int argc, char** argv) {

    // Launch the game
    main_display_menu();
    thread gameThread(&startGame);
    thread displayThread(&main_display, argc, argv);

    displayThread.join();
    gameThread.join();

    return 0;
}