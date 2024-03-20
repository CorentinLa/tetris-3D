#include "board.hpp"
#include "piece.hpp"
#include "game.hpp"

using namespace std;

int Game::readPiecesShapes()
{
    // Read the pieces shapes from a file

    // Store the pieces shapes in a vector of vectors of Coordinates
    fstream piecesFile;
    piecesFile.open("./resources/data/pieces.cfg");
    if (!piecesFile)
    {
        cout << "Error: cannot open pieces.cfg" << endl;
        return 1;
    }

    while (!piecesFile.eof())
    {
        string line;
        getline(piecesFile, line);

        if (line[0] == '#')
        {
            continue;
        }
        else
        {
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
            while (line != "end")
            {
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

int Game::currentPieceMovable(char direction) const
{
    // Move the current piece in the given direction
    // Return 1 if the move is possible, 0 if not
    // Check if the move is possible
    int x = currentPiece.getX();
    int y = currentPiece.getY();
    int z = currentPiece.getZ();
    vector<Coordinates> shape = currentPiece.getShape();
    for (int i = 0; i < shape.size(); i++)
    {
        switch (direction)
        {
        case 'X':
            if (x + shape[i].x + 1 >= board.getWidth())
            {
                return 0;
            }
            if (board.getBoardMat()[x + shape[i].x + 1][y + shape[i].y][z + shape[i].z] >= 2)
            {
                return 0;
            }
            break;
        case 'Y':
            if (y + shape[i].y + 1 >= board.getDepth())
            {
                return 0;
            }
            if (board.getBoardMat()[x + shape[i].x][y + shape[i].y + 1][z + shape[i].z] >= 2)
            {
                return 0;
            }
            break;
        case 'Z':
            if (z + shape[i].z + 1 >= board.getHeight())
            {
                return 0;
            }
            if (board.getBoardMat()[x + shape[i].x][y + shape[i].y][z + shape[i].z + 1] >= 2)
            {
                return 0;
            }
            break;
        case 'x':
            if (x + shape[i].x - 1 < 0)
            {
                return 0;
            }
            if (board.getBoardMat()[x + shape[i].x - 1][y + shape[i].y][z + shape[i].z] >= 2)
            {
                return 0;
            }
            break;
        case 'y':
            if (y + shape[i].y - 1 < 0)
            {
                return 0;
            }
            if (board.getBoardMat()[x + shape[i].x][y + shape[i].y - 1][z + shape[i].z] >= 2)
            {
                return 0;
            }
            break;
        case 'z':
            if (z + shape[i].z - 1 < 0 || z + shape[i].z - 1 >= board.getHeight())
            {
                return 0;
            }
            if (board.getBoardMat()[x + shape[i].x][y + shape[i].y][z + shape[i].z - 1] >= 2)
            {
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

int Game::currentPieceRotatable(char axe, char sens) const
{
    // Rotate the current piece
    // Return 1 if the rotation is possible, 0 if not

    // Check if the rotation is possible
    vector<Coordinates> shape = currentPiece.getShape();
    int x_piece = currentPiece.getX();
    int y_piece = currentPiece.getY();
    int z_piece = currentPiece.getZ();

    float centre_x = 0;
    float centre_y = 0;
    float centre_z = 0;

    // calculate the center of the piece

    for (int i = 0; i < shape.size(); i++)
    {
        centre_x += shape[i].x;
        centre_y += shape[i].y;
        centre_z += shape[i].z;
    }
    centre_x /= shape.size();
    centre_y /= shape.size();
    centre_z /= shape.size();

    switch (axe)
    {
    case 'z':
        if (sens == 'p')
        {
            for (int i = 0; i < shape.size(); i++)
            {
                int x_temp = shape[i].x;
                int x = -(shape[i].y - (int)centre_y);
                int y = x_temp - (int)centre_x;
                if (currentPiece.getX() + x < 0 || currentPiece.getX() + x >= board.getWidth())
                {
                    return 0;
                }
                if (currentPiece.getY() + y < 0 || currentPiece.getY() + y >= board.getDepth())
                {
                    return 0;
                }
                if (currentPiece.getZ() + shape[i].z < 0 || currentPiece.getZ() + shape[i].z >= board.getHeight())
                {
                    return 0;
                }
                if (board.getBoardMat()[x_piece + x][y_piece + y][z_piece + shape[i].z] >= 2)
                {
                    return 0;
                }
            }
        }
        else if (sens == 'n')
        {
            for (int i = 0; i < shape.size(); i++)
            {
                int x_temp = shape[i].x;
                int x = shape[i].y - centre_y;
                int y = -(x_temp - centre_x);
                if (currentPiece.getX() + x < 0 || currentPiece.getX() + x >= board.getWidth())
                    return 0;
                if (currentPiece.getY() + y < 0 || currentPiece.getY() + y >= board.getDepth())
                    return 0;
                if (currentPiece.getZ() + shape[i].z < 0 || currentPiece.getZ() + shape[i].z >= board.getHeight())
                    return 0;
                if (board.getBoardMat()[x_piece + x][y_piece + y][z_piece + shape[i].z] >= 2)
                    return 0;
            }
        }
        else
        {
            cout << "Error: sens must be p or n" << endl;
            return 0;
        }
        break;
    case 'x':
        if (sens == 'p')
        {
            for (int i = 0; i < shape.size(); i++)
            {
                int y_temp = shape[i].y;
                int y = -(shape[i].z - centre_z);
                int z = y_temp - centre_y;
                if (currentPiece.getX() + shape[i].x < 0 || currentPiece.getX() + shape[i].x >= board.getWidth())
                    return 0;
                if (currentPiece.getY() + y < 0 || currentPiece.getY() + y >= board.getDepth())
                    return 0;
                if (currentPiece.getZ() + z < 0 || currentPiece.getZ() + z >= board.getHeight())
                    return 0;
                if (board.getBoardMat()[x_piece + shape[i].x][y_piece + y][z_piece + z] >= 2)
                    return 0;
            }
        }
        else if (sens == 'n')
        {
            for (int i = 0; i < shape.size(); i++)
            {
                int y_temp = shape[i].y;
                int y = shape[i].z - centre_z;
                int z = -(y_temp - centre_y);
                if (currentPiece.getX() + shape[i].x < 0 || currentPiece.getX() + shape[i].x >= board.getWidth())
                    return 0;
                if (currentPiece.getY() + y < 0 || currentPiece.getY() + y >= board.getDepth())
                    return 0;
                if (currentPiece.getZ() + z < 0 || currentPiece.getZ() + z >= board.getHeight())
                    return 0;
                if (board.getBoardMat()[x_piece + shape[i].x][y_piece + y][z_piece + z] >= 2)
                    return 0;
            }
        }
        else
        {
            cout << "Error: sens must be p or n" << endl;
            return 0;
        }
    case 'y':
        if (sens == 'p')
        {
            for (int i = 0; i < shape.size(); i++)
            {
                int x_temp = shape[i].x;
                int x = -(shape[i].z - centre_z);
                int z = x_temp - centre_x;
                if (currentPiece.getX() + x < 0 || currentPiece.getX() + x >= board.getWidth())
                    return 0;
                if (currentPiece.getZ() + z < 0 || currentPiece.getZ() + z >= board.getHeight())
                    return 0;
                if (currentPiece.getY() + shape[i].y < 0 || currentPiece.getY() + shape[i].y >= board.getDepth())
                    return 0;
                if (board.getBoardMat()[x_piece + x][y_piece + shape[i].y][z_piece + z] >= 2)
                    return 0;
            }
        }
        else if (sens == 'n')
        {
            for (int i = 0; i < shape.size(); i++)
            {
                int x_temp = shape[i].x;
                int x = shape[i].z - centre_z;
                int z = -(x_temp - centre_x);
                if (currentPiece.getX() + x < 0 || currentPiece.getX() + x >= board.getWidth())
                    return 0;
                if (currentPiece.getY() + shape[i].y < 0 || currentPiece.getY() + shape[i].y >= board.getDepth())
                    return 0;
                if (currentPiece.getZ() + z < 0 || currentPiece.getZ() + z >= board.getHeight())
                    return 0;
                if (board.getBoardMat()[x_piece + x][y_piece + shape[i].y][z_piece + z] >= 2)
                    return 0;
            }
        }
        else
        {
            cout << "Error: sens must be p or n" << endl;
            return 0;
        }
    }
    return 1;
}

int Game::gameLoop()
{
    // Main game loop
    // Return 0 if the game is over, 1 if not
    // Try to move the current piece down
    time += 1;

    if (currentPieceMovable('z') == 0)
    {
        // If the move is not possible, put the piece in the board
        board.constructPiece(currentPiece, 2);
        int ***boardMat = board.getBoardMat();
        int x = currentPiece.getX();
        int y = currentPiece.getY();
        int z = currentPiece.getZ();

        // Check if a line is complete
        int lineXComplete = 1;
        int lineYComplete = 1;

        int nb_LinesX = 0;
        int nb_LinesY = 0;

        for (int k = -5; k < z + 5 && k < board.getHeight(); k++)
        {
            if (k <= 0)
                continue;
            for (int i = 0; i < board.getWidth(); i++)
            {
                for (int j = 0; j < board.getDepth(); j++)
                {
                    if (boardMat[i][j][k] != 2)
                    {
                        lineXComplete = 0;
                        break;
                    }
                }
                if (lineXComplete == 1)
                {
                    board.removeLine('x', i, k);
                    nb_LinesX++;
                }
                else
                {
                    lineXComplete = 1;
                }
            }

            for (int i = 0; i < board.getDepth() - 1; i++)
            {
                for (int j = 0; j < board.getWidth(); j++)
                {
                    if (boardMat[j][i][k] != 2)
                    {
                        lineYComplete = 0;
                        break;
                    }
                }
                if (lineYComplete == 1)
                {
                    board.removeLine('y', i, k);
                    nb_LinesY++;
                }
                else
                {
                    lineYComplete = 1;
                }
            }
        }
        setScore(score + params.difficulty * sqrt(getTime()) * 10);
        if (nb_LinesX > 0 || nb_LinesY > 0)
        {
            std::thread([this]
                        {
                music sound("resources/sounds/line_complete.wav", min(params.volume+10, 100));
                this_thread::sleep_for(chrono::milliseconds(1000)); })
                .detach();
        }
        else
        {
            std::thread([this]
                        {
                music sound("resources/sounds/piece_landing.flac", min(params.volume+10, 100));
                this_thread::sleep_for(chrono::milliseconds(1000)); })
                .detach();
        }
        while (nb_LinesX > 0 or nb_LinesY > 0)
        {
            if (nb_LinesX > 0 && nb_LinesY > 0)
            {
                setScore(score + params.difficulty * sqrt(getTime()) * 1000);
                nb_LinesX--;
                nb_LinesY--;
            }
            else if (nb_LinesX > 0)
            {
                setScore(score + params.difficulty * sqrt(getTime()) * 100);
                nb_LinesX--;
            }
            else if (nb_LinesY > 0)
            {
                setScore(score + params.difficulty * sqrt(getTime()) * 100);
                nb_LinesY--;
            }
        }

        // Check if the game is over
        for (int i = 0; i < board.getWidth(); i++)
        {
            for (int j = 0; j < board.getDepth(); j++)
            {
                if (j >= board.getDepth() || j < 0)
                    continue;
                if (boardMat[i][j][board.getHeight() - 1] == 2)
                {
                    cout << "Game over" << endl;
                    return 0;
                }
            }
        }

        // Change the pieces
        changeCurrentPiece();
        changeNextPiece();
    }
    else
    {
        // If the move is possible, destroy the current piece and construct it at its new position
        // board.constructPiece(currentPiece, 0);
        destroyCurrentPiece();
        // Construct the piece at its new position
        moveCurrentPiece('z');
        constructCurrentPiece();
        // board.constructPiece(currentPiece, 1);
    }

    // change time using timestamp

    return 1;
}
