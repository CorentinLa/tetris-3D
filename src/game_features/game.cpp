#include "board.hpp"
#include "piece.hpp"
#include "game.hpp"

using namespace std;

// int startGame(int width, int height, int depth) {
//     Board board(width, height, depth);
//     Piece piece;
//     board.constructPiece(piece);
//     return 0;
// }


int Game::readPiecesShapes() {
    // Read the pieces shapes from a file

    // Store the pieces shapes in a vector of vectors of Coordinates
    fstream piecesFile;
    piecesFile.open("./resources/data/pieces.cfg");
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
    // cout << pieceShapes.size() << " pieces shapes read" << endl;

    return 0;
}

int Game::currentPieceMovable(char direction) const {
    // Move the current piece in the given direction
    // Return 1 if the move is possible, 0 if not

    // Check if the move is possible
    int x = currentPiece.getX();
    int y = currentPiece.getY();
    int z = currentPiece.getZ();
    vector<Coordinates> shape = currentPiece.getShape();
    for(int i=0; i< shape.size(); i++) {
        switch(direction) {
            case 'X':
                if(x+shape[i].x+1 >= board.getWidth()) {
                    return 0;
                }
                if(board.getBoardMat()[x+shape[i].x+1][y+shape[i].y][z+shape[i].z] == 2) {
                    return 0;
                }
                break;
            case 'Y':
                if(y+shape[i].y+1 >= board.getDepth()) {
                    return 0;
                }
                if(board.getBoardMat()[x+shape[i].x][y+shape[i].y+1][z+shape[i].z] == 2) {
                    return 0;
                }
                break;
            case 'Z':
                if(z+shape[i].z+1 >= board.getHeight()) {
                    return 0;
                }
                if(board.getBoardMat()[x+shape[i].x][y+shape[i].y][z+shape[i].z+1] == 2) {
                    return 0;
                }
                break;
            case 'x':
                if(x+shape[i].x-1 < 0) {
                    return 0;
                }
                if(board.getBoardMat()[x+shape[i].x-1][y+shape[i].y][z+shape[i].z] == 2) {
                    return 0;
                }
                break;
            case 'y':
                if(y+shape[i].y-1 < 0) {
                    return 0;
                }
                if(board.getBoardMat()[x+shape[i].x][y+shape[i].y-1][z+shape[i].z] == 2) {
                    return 0;
                }
                break;
            case 'z':
                if(z+shape[i].z-1 < 0 || z+shape[i].z-1 >= board.getHeight()) return 0;

                if(board.getBoardMat()[x+shape[i].x][y+shape[i].y][z+shape[i].z-1] == 2) {
                    return 0;
                }
                break;    
        
            default:
                cout << "Error: direction must be X,Y,Z, x, y or z" << endl;
                break;
        }
    }

    return 1;
}

int Game::gameLoop() {
    // Main game loop
    // Return 0 if the game is over, 1 if not
    // Try to move the current piece down
    if(currentPieceMovable('z') == 0) {
        // If the move is not possible, put the piece in the board
        board.constructPiece(currentPiece, 2);
        int *** boardMat = board.getBoardMat();
        int x = currentPiece.getX();
        int y = currentPiece.getY();
        int z = currentPiece.getZ();
        vector<Coordinates> shape = currentPiece.getShape();

        // Check if a line is complete
        int lineXComplete = 1;
        int lineYComplete = 1;

        int nb_LinesX = 0;
        int nb_LinesY = 0;


        for(int k=z; k<z+4 && k < board.getHeight(); k++) {
            if (k == 0) continue;
        for(int i=x; i<x+4 && i < board.getWidth(); i++) {
            for(int j=0; j<board.getDepth(); j++) {
                if(boardMat[i][j][k] != 2) {
                    lineXComplete = 0;
                    break;
                }
                }
                if (lineXComplete == 1) {
                    board.removeLine('x', i, k);
                    nb_LinesX++;
                } else {
                    lineXComplete = 1;
                }
            }

        for(int i=y; i<y+4 && i < board.getDepth(); i++) {
            for(int j=0; j<board.getWidth(); j++) {
                if(boardMat[j][i][k] != 2) {
                    lineYComplete = 0;
                    break;
                }
                }
                if (lineYComplete == 1) {
                    board.removeLine('y', i, k);
                    nb_LinesY++;
                } else {
                    lineYComplete = 1;
                }
            }
        }
        setScore(score+sqrt(getTime())*10);
        while(nb_LinesX > 0 or nb_LinesY > 0) {
            if(nb_LinesX > 0 && nb_LinesY > 0) {
                setScore(score+sqrt(getTime())*1000);
                nb_LinesX--;
                nb_LinesY--;
            } else if(nb_LinesX > 0) {
                setScore(score+sqrt(getTime())*100);
                nb_LinesX--;
            } else if(nb_LinesY > 0) {
                setScore(score+sqrt(getTime())*100);
                nb_LinesY--;
            }
        }

        // Check if the game is over
        for(int i=x; i<x+4 && i < board.getWidth(); i++) {
            for(int j=y; j<y+4 && j < board.getDepth(); j++) {
                if(boardMat[i][j][board.getHeight()-1] == 2) {
                    cout << "Game over" << endl;
                    return 0;
                }
            }
        }

        // Change the pieces
        changeCurrentPiece();
        changeNextPiece();

    } else {
        // If the move is possible, destroy the current piece and construct it at its new position
        board.constructPiece(currentPiece, 0);

        // Construct the piece at its new position
        moveCurrentPiece('z');
        board.constructPiece(currentPiece, 1);
    }


    // change time using timestamp

    return 1;
}
