#ifndef DISPLAY_GAME_HPP
#define DISPLAY_GAME_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <stdexcept>
#include <new>
#include "../../game_features/game.hpp"
#include <mutex>

#define KEY_ESCAPE 27

using namespace std;

typedef struct {
	int width;
	int height;
	char* title;
	float field_of_view_angle;
	float z_near;
	float z_far;
}glutWindow;

void initGame(Game* startedGame);

void drawCube(float x, float y, float z, float size, GLuint textureID);

void drawBackground(GLuint textureID);

void drawGrid();

GLuint loadTexture(const char* filename);

void update_game(int*** new_base, int base_width, int base_depth, int base_height);

int main_display(int argc, char** argv);

#endif