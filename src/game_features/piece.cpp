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
    switch(axe)
    {
        case 'x':
            if(sens == 'p')
            {
                for (int i = 0; i < shape.size(); i++)
                {
                    int y = shape[i].y;
                    shape[i].y = -shape[i].z;
                    shape[i].z = y;
                }
            }
            else if(sens == 'n')
            {
                for (int i = 0; i < shape.size(); i++)
                {
                    int y = shape[i].y;
                    shape[i].y = shape[i].z;
                    shape[i].z = -y;
                }
            }
            break;
        case 'y':
            if(sens == 'p')
            {
                for (int i = 0; i < shape.size(); i++)
                {
                    int x = shape[i].x;
                    shape[i].x = -shape[i].z;
                    shape[i].z = x;
                }
            }
            else if(sens == 'n')
            {
                for (int i = 0; i < shape.size(); i++)
                {
                    int x = shape[i].x;
                    shape[i].x = shape[i].z;
                    shape[i].z = -x;
                }
            }
            break;
        case 'z':
            if(sens == 'p')
            {
                for (int i = 0; i < shape.size(); i++)
                {
                    int x = shape[i].x;
                    shape[i].x = -shape[i].y;
                    shape[i].y = x;
                }
            }
            else if(sens == 'n')
            {
                for (int i = 0; i < shape.size(); i++)
                {
                    int x = shape[i].x;
                    shape[i].x = shape[i].y;
                    shape[i].y = -x;
                }
            }
            break;
        default:
            std::cout << "Error: axe must be x y or z" << std::endl;
            break;
    }
}
