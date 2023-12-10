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

void setShape(int[4][4][4] matrixShape) // Coordinates start from bottom left front corner of the cube for accessibility. The cube is 4x4x4.
{
    for(int x=0; x<4; x++)
    {
        for(int y=0; y<4; y++)
        {
            for(int z=0; z<4; z++)
            {
                // Shift the shape to the center of the cube
                    

            }
        }
    }   
}