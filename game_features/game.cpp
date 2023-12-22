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

int Game::moveCurrentPiece(char direction) {
    // Move the current piece in the given direction
    // Return 1 if the move is possible, 0 if not

    // Check if the move is possible
    int x = currentPiece.getX();
    int y = currentPiece.getY();
    int z = currentPiece.getZ();
    vector<Coordinates> shape = currentPiece.getShape();
    for(int i=0; i< shape.size(); i++) {
        switch(direction) {
            case 'xP':
                if(board.getBoardMat()[x+shape[i].x+1][y+shape[i].y][z+shape[i].z] == 2) {
                    return 0;
                }
                break;
            case 'yP':
                if(board.getBoardMat()[x+shape[i].x][y+shape[i].y+1][z+shape[i].z] == 2) {
                    return 0;
                }
                break;
            case 'zP':
                if(board.getBoardMat()[x+shape[i].x][y+shape[i].y][z+shape[i].z+1] == 2) {
                    return 0;
                }
                break;
            case 'xN':
                if(board.getBoardMat()[x+shape[i].x-1][y+shape[i].y][z+shape[i].z] == 2) {
                    return 0;
                }
                break;
            case 'yN':
                if(board.getBoardMat()[x+shape[i].x][y+shape[i].y-1][z+shape[i].z] == 2) {
                    return 0;
                }
                break;
            case 'zN':
                if(board.getBoardMat()[x+shape[i].x][y+shape[i].y][z+shape[i].z-1] == 2) {
                    return 0;
                }
                break;    
        
            default:
                cout << "Error: direction must be x, y or z" << endl;
                break;
        }
    }

    // If the move is possible, move the piece
    switch(direction) {
        case 'x':
            currentPiece.setX(x+1);
            break;
        case 'y':
            currentPiece.setY(y+1);
            break;
        case 'z':
            currentPiece.setZ(z+1);
            break;
        case 'xN':
            currentPiece.setX(x-1);
            break;
        case 'yN':
            currentPiece.setY(y-1);
            break;
        case 'zN':
            currentPiece.setZ(z-1);
            break;

        default:
            cout << "Error: direction must be xP, yP, zP, xN, yN or zN" << endl;
            break;
    }
    return 1;
}

int Game::gameLoop() {
    // Main game loop
    // Return 0 if the game is over, 1 if not

    // Try to move the current piece down
    if(moveCurrentPiece('zN') == 0) {
        // If the move is not possible, put the piece in the board
        board.constructPiece(currentPiece, 2);

        // Check if the game is over
        int *** boardMat = board.getBoardMat();
        int x = currentPiece.getX();
        int y = currentPiece.getY();
        int z = currentPiece.getZ();

        // Check if a line is complete
        for(int i=x; i<x+4; i++) {
            for(int j=0; j<board.getDepth(); j++) {
                int lineXComplete = 1;
                if(boardMat[i][j][z] != 2) {
                    lineXComplete = 0;
                    break;
                }
                }
            }
        }
        for(int i=y; i<y+4; i++) {
            for(int j=0; j<board.getDepth(); j++) {
                int lineYComplete = 1;
                if(boardMat[j][i][z] != 2) {
                    lineYComplete = 0;
                    break;
                }
                }
            }
        }
        setScore(score+sqrt(getTime())*10);
        if(lineXComplete == 1 && lineYComplete == 1) {
            // Remove the line
            board.removeLine('x', x, z);
            board.removeLine('y', y, z);
            setScore(score+sqrt(getTime())*1000);
        }
        else if(lineXComplete == 1) {
            board.removeLine('x', x, z);
            setScore(score+sqrt(getTime())*100);
        }
        else if(lineYComplete == 1) {
            board.removeLine('y', y, z);
            setScore(score+sqrt(getTime())*100);
        }


        for(int i=x; i<x+4; i++) {
            for(int j=y; j<y+4; j++) {
                if(boardMat[i][j][board.getHeight()-1] == 2) {
                    return 0;
                }
            }
        }

    } else {
        board.constructPiece(currentPiece, 0);
        board.constructPiece(currentPiece, 1);
    }

    // Change the pieces
    changeCurrentPiece();
    changeNextPiece();

    // change time using timestamp

    return 1;
}


int main(){
    
}