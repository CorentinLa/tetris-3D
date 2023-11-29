


class Piece
{

private:
    int x;
    int y;
    int z;
    int rotation_x;
    int rotation_y;
    int rotation_z;
    int shape[4][4][4]; // 4x4x4 matrix with x y z coordinates relative to the piece

    void setRotation(char axe, int angle); // angle in degrees

public:
    Piece();
    Piece(int x, int y, int z);
    ~Piece();

    void setX(int x);
    void setY(int y);
    void setZ(int z);

    // Angles in degrees (must be a multiple of 90)
    void setRotationX(int angle) setRotation('x', angle);
    void setRotationY(int angle) setRotation('y', angle);
    void setRotationZ(int angle) setRotation('z', angle);

    int getX() const return x;
    int getY() const return y;
    int getZ() const return z;

    int getRotationX() const return rotation_x;
    int getRotationY() const return rotation_y;
    int getRotationZ() const return rotation_z;

    int[4][4][4] getShape() return shape;
};