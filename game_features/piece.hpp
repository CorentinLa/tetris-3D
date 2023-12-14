#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>
#include <iostream>

using namespace std;

class Coordinates
{
public:
    int x;
    int y;
    int z;

    Coordinates(): x(0), y(0), z(0) {};
    Coordinates(int xn, int yn, int zn): x(xn), y(yn), z(zn) {};
};

class Piece
{
private:
    Coordinates coord;
    int rotation_x;
    int rotation_y;
    int rotation_z;
    vector<float> color; // RGB values between 0 and 1
    vector<Coordinates> shape; // Coordinates of cubes in the piece

public:
    Piece(): rotation_x(0), rotation_y(0), rotation_z(0), color(3, 0.0f) {};
    Piece(int x, int y, int z): coord(x, y, z), rotation_x(0), rotation_y(0), rotation_z(0), color(3, 0.0f) {};
    Piece(int x, int y, int z, float r, float g, float b): coord(x,y,z), rotation_x(0), rotation_y(0), rotation_z(0), color(3, 0.0f) 
    {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    };

    // Copy 
    Piece(const Piece& oldPiece) = default;

    void setRotationX(int angle) { setRotation('x', angle); }; // future : rotation relative to the current rotation on the screen;
    void setRotationY(int angle) { setRotation('y', angle); };
    void setRotationZ(int angle) { setRotation('z', angle); };

    void setShape(int matrixShape[4][4][4]); 
    
    void setColor(float r, float g, float b) 
    {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    };

    void setX(int x) { coord.x = x; };
    void setY(int y) { coord.y = y; };
    void setZ(int z) { coord.z = z; };

    void setCoord(int x, int y, int z) { coord.x = x; coord.y = y; coord.z = z; };


    int getX() const { return coord.x; };
    int getY() const { return coord.y; };
    int getZ() const { return coord.z; };

    int getRotationX() const { return rotation_x; };
    int getRotationY() const { return rotation_y; };
    int getRotationZ() const { return rotation_z; };

    vector<float> getColor() const { return color;};

    vector<Coordinates> getShape() {return shape;};

    void setRotation(char axe, int angle); // angle in degrees

};

#endif