/* Main class for the 3D Tetris*/

#include "board.hpp"
#include "piece.hpp"
#include "game.hpp"

using namespace std;

int startGame(int width, int height, int depth) {
    Board board(width, height, depth);
    Piece piece;
    board.constructPiece(piece);
    return 0;
}



int Game::readPiecesShapes() {
    // Read the pieces shapes from a file

    // Store the pieces shapes in a vector of vectors of Coordinates
    fstream piecesFile;
    piecesFile.open("../data/pieces.cfg");
    if(!piecesFile) {
        cout << "Error: cannot open pieces.cfg" << endl;
        return 1;
    }

    while(!piecesFile.eof()) {
        string line;
        getline(piecesFile, line);
        
        if(line[0] == '#') {
            continue;
        }
        else {
            // Read the coordinates of the piece
            /*
            File format:
            x y z
            x y z
            ...
            end
            x y z
            ...
            end
            
            */
            vector<Coordinates> pieceShape;
            while(line != "end") {
                int x, y, z;
                sscanf(line.c_str(), "%d %d %d", &x, &y, &z);
                Coordinates coord(x, y, z);
                pieceShape.push_back(coord);
                getline(piecesFile, line);
            }
            pieceShapes.push_back(pieceShape);
        }
    }

    return 0;
}


int main(){
    
}