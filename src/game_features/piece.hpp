#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class Coordinates
{
public:
    int x;
    int y;
    int z;

    Coordinates() : x(0), y(0), z(0){};
    Coordinates(int xn, int yn, int zn) : x(xn), y(yn), z(zn){};
};

/**
 * Represents a piece in the game.
 * A piece is a vector of coordinates representing the position of the cubes in the piece.
 * Exemple : [[0, 0, 0], [0, 1, 0], [0, 2, 0]] represents a horizontal line of 3 cubes.
 */
class Piece
{
private:
    Coordinates coord;
    vector<Coordinates> shape; // Coordinates of cubes in the piece

public:
    Piece() {};
    Piece(int x, int y, int z) : coord(x, y, z) {};

    // Copy
    Piece(const Piece &oldPiece) = default;

    void setShape(vector<Coordinates> newShape) { shape = newShape; };

    void setX(int x) { coord.x = x; };
    void setY(int y) { coord.y = y; };
    void setZ(int z) { coord.z = z; };

    void setCoord(int x, int y, int z)
    {
        coord.x = x;
        coord.y = y;
        coord.z = z;
    };

    int getX() const { return coord.x; };
    int getY() const { return coord.y; };
    int getZ() const { return coord.z; };

    vector<Coordinates> getShape() const { return shape; };

    /**
     * Rotates the piece around a specified axis.
     *
     * @param axe The axis of rotation ('x', 'y', or 'z').
     * @param sens The direction of rotation ('p' for positive or 'n' for negative).
     */
    void rotate(char axe, char sens); // sens = p or n
};

#endif