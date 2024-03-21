#include "piece.hpp"

/**
 * Rotates the piece around a specified axis.
 * The idea is to rotate the piece around the center of the piece.
 * To do so, we substract the center coordinates from the coordinates of each cube of the piece and then apply the matrix of rotation.
 *
 * @param axe The axis of rotation ('x', 'y', or 'z').
 * @param sens The direction of rotation ('p' for positive or 'n' for negative).
 */
void Piece::rotate(char axe, char sens)
{
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

    // Convert to integers
    centre_x = round(centre_x);
    centre_y = round(centre_y);
    centre_z = round(centre_z);

    switch (axe)
    {
    case 'x':
        if (sens == 'p')
        {
            for (int i = 0; i < shape.size(); i++)
            {
                int y = shape[i].y;
                shape[i].y = -(shape[i].z - centre_z);
                shape[i].z = y - centre_y;
            }
        }
        else if (sens == 'n')
        {
            for (int i = 0; i < shape.size(); i++)
            {
                int y = shape[i].y;
                shape[i].y = shape[i].z - centre_z;
                shape[i].z = -(y - centre_y);
            }
        }
        break;
    case 'y':
        if (sens == 'p')
        {
            for (int i = 0; i < shape.size(); i++)
            {
                int x = shape[i].x;
                shape[i].x = -(shape[i].z - centre_z);
                shape[i].z = x - centre_x;
            }
        }
        else if (sens == 'n')
        {
            for (int i = 0; i < shape.size(); i++)
            {
                int x = shape[i].x;
                shape[i].x = shape[i].z - centre_z;
                shape[i].z = -(x - centre_x);
            }
        }
        break;
    case 'z':
        if (sens == 'p')
        {
            for (int i = 0; i < shape.size(); i++)
            {
                int x = shape[i].x;
                shape[i].x = -(shape[i].y - centre_y);
                shape[i].y = x - centre_x;
            }
        }
        else if (sens == 'n')
        {
            for (int i = 0; i < shape.size(); i++)
            {
                int x = shape[i].x;
                shape[i].x = shape[i].y - centre_y;
                shape[i].y = -(x - centre_x);
            }
        }
        break;
    default:
        std::cout << "Error: axe must be x y or z" << std::endl;
        break;
    }
}
