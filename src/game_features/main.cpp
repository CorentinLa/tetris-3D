#include"main.hpp"
using namespace std;

mutex mtx;
// The game will have to lock when it reads the keyboard input

int startGame() {
    Game onGoingGame(10, 10, 10);
    // Launch keyboard reading thread

    // Launch main loop
    int gameEnded = 1;
    while(gameEnded) {
        unique_lock<mutex> lck(mtx);
        gameEnded = onGoingGame.gameLoop();
        Board board = onGoingGame.getBoard();
        
        // Wait for a while
        this_thread::sleep_for(chrono::milliseconds(1000/onGoingGame.getDifficulty()));
        
        // TEMPORARY : Print the board
        
        int*** boardMat = board.getBoardMat();
        int width = board.getWidth(); 
        int depth = board.getDepth();
        int height = board.getHeight();

        update_game(boardMat, width);

        // for(int k = 0; k < height; k++) {
        //     for(int i = 0; i < width; i++) {
        //         for(int j = 0; j < depth; j++) {
        //             cout << boardMat[i][j][k] << " ";
        //         }
        //         cout << endl;
        //     }
        //     cout << endl;
        // }

        // TEMPORARY : Print the top level of the board
        // for(int i = 0; i < width; i++) {
        //     for(int j = 0; j < depth; j++) {
        //         cout << boardMat[i][j][height-1] << " ";
        //     }
        //     cout << endl;
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