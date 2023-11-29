#include "piece.hpp"


void setRotation(char axe, int angle) // angle in degrees
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