#include"main.hpp"
using namespace std;

mutex mtx;
// The game will have to lock when it reads the keyboard input

int startGame() {
    Game onGoingGame(15, 15, 15);
    // Launch keyboard reading thread
    initGame(&onGoingGame);

    // Launch main loop
    int gameEnded = 1;
    while(gameEnded) {
        unique_lock<mutex> lck(mtx);
        gameEnded = onGoingGame.gameLoop();
        Board board = onGoingGame.getBoard();
        int*** boardMat = board.getBoardMat();
        int width = board.getWidth(); 
        update_game(boardMat, width);
        
        // Wait for a while
        this_thread::sleep_for(chrono::milliseconds(1000/onGoingGame.getDifficulty()));
        
        // TEMPORARY : Print the board
        
        
        
        int depth = board.getDepth();
        int height = board.getHeight();

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

int playMusic() {
    // Play the music 
    libvlc_instance_t *inst;
    const char * const vlc_args[] = {
        "--file-caching=20000"  // Set the file caching value to 10000 milliseconds (10 seconds)
    };
    inst = libvlc_new(1, vlc_args);
    char const *location = "./resources/sounds/classic_tetris.flac";
    libvlc_media_t *vlc_media = libvlc_media_new_path(inst, location);

    libvlc_media_player_t *vlc_player = libvlc_media_player_new_from_media(vlc_media);
    libvlc_audio_set_volume(vlc_player, 20);
    libvlc_media_player_play(vlc_player); //this line will play the video and audio

    // while(1) {
    //     libvlc_media_player_stop(vlc_player);
    //     libvlc_media_player_play(vlc_player);
    // }
    std::this_thread::sleep_for(std::chrono::minutes(5)); // adjust the delay as needed
    

    return 0;
}

int main(int argc, char** argv) {
    // Launch the interface
    // thread interfaceThread(&interface);

    // start musing on a separate process and not thread.
    // thread musicThread(&playMusic);
    // musicThread.detach();

    // Launch the game
    thread gameThread(&startGame);
    thread displayThread(&main_display, argc, argv);
    
    displayThread.join();
    gameThread.join();

    return 0;
}