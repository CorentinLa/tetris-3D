#include <vector>

using namespace std;
class Piece
{

private:
    int x;
    int y;
    int z;
    int rotation_x;
    int rotation_y;
    int rotation_z;
    vector<vector<vector<int>>> shape; // Array of 3D vectors. Each vector is a point of the shape. The shape is a 4x4x4 cube. The points are relative to the center of the cube.

    void setRotation(char axe, int angle); // angle in degrees

public:
    Piece();
    Piece(int x, int y, int z);
    ~Piece();

    void setX(int x);
    void setY(int y);
    void setZ(int z);

    // Angles in degrees (must be a multiple of 90)
    void setRotationX(int angle) setRotation('x', angle); // future : rotation relative to the current rotation on the screen
    void setRotationY(int angle) setRotation('y', angle);
    void setRotationZ(int angle) setRotation('z', angle);

    void setShape(int[4][4][4] matrixShape); // Coordinates start from bottom left front corner of the cube for accessibility. The cube is 4x4x4.

    int getX() const return x;
    int getY() const return y;
    int getZ() const return z;

    int getRotationX() const return rotation_x;
    int getRotationY() const return rotation_y;
    int getRotationZ() const return rotation_z;

    vector<vector<vector<int>>> getShape() return shape;
};