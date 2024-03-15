#include "piece.hpp"


void Piece::setRotation(char axe, int angle) // angle in degrees
{
    if(angle % 90 != 0)
    {
        std::cout << "Error: angle must be a multiple of 90 degrees" << std::endl;
        return;
    }
    switch(axe)
    {
        case 'x':
            rotation_x = angle;
            break;
        case 'y':
            rotation_y = angle;
            break;
        case 'z':
            rotation_z = angle;
            break;
        default:
            std::cout << "Error: axe must be x, y or z" << std::endl;
            break;
    }
}

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

    switch(axe)
    {
        case 'x':
            if(sens == 'p')
            {
                for (int i = 0; i < shape.size(); i++)
                {
                    int y = shape[i].y;
                    shape[i].y = -(shape[i].z-centre_z);
                    shape[i].z = y-centre_y;

                }
            }
            else if(sens == 'n')
            {
                for (int i = 0; i < shape.size(); i++)
                {
                    int y = shape[i].y;
                    shape[i].y = shape[i].z - centre_z;
                    shape[i].z = -(y-centre_y);
                }
            }
            break;
        case 'y':
            if(sens == 'p')
            {
                for (int i = 0; i < shape.size(); i++)
                {
                    int x = shape[i].x;
                    shape[i].x = -(shape[i].z-centre_z);
                    shape[i].z = x-centre_x;
                }
            }
            else if(sens == 'n')
            {
                for (int i = 0; i < shape.size(); i++)
                {
                    int x = shape[i].x;
                    shape[i].x = shape[i].z-centre_z;
                    shape[i].z = -(x-centre_x);
                }
            }
            break;
        case 'z':
            if(sens == 'p')
            {
                for (int i = 0; i < shape.size(); i++)
                {
                    int x = shape[i].x;
                    shape[i].x = -(shape[i].y-centre_y);
                    shape[i].y = x-centre_x;
                }
            }
            else if(sens == 'n')
            {
                for (int i = 0; i < shape.size(); i++)
                {
                    int x = shape[i].x;
                    shape[i].x = shape[i].y-centre_y;
                    shape[i].y = -(x-centre_x);
                }
            }
            break;
        default:
            std::cout << "Error: axe must be x y or z" << std::endl;
            break;
    }
}
