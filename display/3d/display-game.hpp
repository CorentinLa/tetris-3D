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


GLuint cobblestoneID;
GLuint floorID;
GLuint fujisanID;

#define KEY_ESCAPE 27
#define N 15.00

using namespace std;

typedef struct {
	int width;
	int height;
	char* title;
	float field_of_view_angle;
	float z_near;
	float z_far;
}glutWindow;

glutWindow win;

bool fullscreen = false;

int d = N;
int texture_size = 16;
int upDown_x = 0;
int upDown_z = 0;
int leftRight_rotation = 45;
int r_speed = 7;
int zoom = 40;
float movex = -1;
float movez = -1;
const int base_size = 15;
bool gameOver = false;

bool stop = true;
int base[base_size][base_size][base_size];
 
void *font = GLUT_BITMAP_HELVETICA_18;

void drawCube(float x, float y, float z, float size, GLuint textureID) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);

    // Front face
    glTexCoord2f(0, 0); glVertex3f(x - size / 2, y - size / 2, z + size / 2);
    glTexCoord2f(1, 0); glVertex3f(x + size / 2, y - size / 2, z + size / 2);
    glTexCoord2f(1, 1); glVertex3f(x + size / 2, y + size / 2, z + size / 2);
    glTexCoord2f(0, 1); glVertex3f(x - size / 2, y + size / 2, z + size / 2);

    // Back face
    glTexCoord2f(1, 0); glVertex3f(x - size / 2, y - size / 2, z - size / 2);
    glTexCoord2f(0, 0); glVertex3f(x + size / 2, y - size / 2, z - size / 2);
    glTexCoord2f(0, 1); glVertex3f(x + size / 2, y + size / 2, z - size / 2);
    glTexCoord2f(1, 1); glVertex3f(x - size / 2, y + size / 2, z - size / 2);

    // Left face
    glTexCoord2f(0, 0); glVertex3f(x - size / 2, y - size / 2, z + size / 2);
    glTexCoord2f(1, 0); glVertex3f(x - size / 2, y - size / 2, z - size / 2);
    glTexCoord2f(1, 1); glVertex3f(x - size / 2, y + size / 2, z - size / 2);
    glTexCoord2f(0, 1); glVertex3f(x - size / 2, y + size / 2, z + size / 2);

    // Right face
    glTexCoord2f(1, 0); glVertex3f(x + size / 2, y - size / 2, z + size / 2);
    glTexCoord2f(0, 0); glVertex3f(x + size / 2, y - size / 2, z - size / 2);
    glTexCoord2f(0, 1); glVertex3f(x + size / 2, y + size / 2, z - size / 2);
    glTexCoord2f(1, 1); glVertex3f(x + size / 2, y + size / 2, z + size / 2);

    // Top face
    glTexCoord2f(0, 1); glVertex3f(x - size / 2, y + size / 2, z + size / 2);
    glTexCoord2f(1, 1); glVertex3f(x + size / 2, y + size / 2, z + size / 2);
    glTexCoord2f(1, 0); glVertex3f(x + size / 2, y + size / 2, z - size / 2);
    glTexCoord2f(0, 0); glVertex3f(x - size / 2, y + size / 2, z - size / 2);

    // Bottom face
    glTexCoord2f(0, 1); glVertex3f(x - size / 2, y - size / 2, z + size / 2);
    glTexCoord2f(1, 1); glVertex3f(x + size / 2, y - size / 2, z + size / 2);
    glTexCoord2f(1, 0); glVertex3f(x + size / 2, y - size / 2, z - size / 2);
    glTexCoord2f(0, 0); glVertex3f(x - size / 2, y - size / 2, z - size / 2);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawFloor(GLuint textureID) {
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    const float tileSize = 1;

    glBegin(GL_QUADS);
    for (int i = -base_size; i < base_size; ++i) {
        for (int j = -base_size; j < base_size; ++j) {
            float x = i * tileSize;
            float z = j * tileSize;

            // Draw each quad with texture coordinates
            glTexCoord2f(0.0f, 0.0f); glVertex3f(x, -base_size/2-1, z);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(x + tileSize, -base_size/2-1, z);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(x + tileSize, -base_size/2-1, z + tileSize);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(x, -base_size/2-1, z + tileSize);
        }
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawBackground(GLuint textureID) {
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);

	int background_size = 8;

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-base_size/2-1, -background_size, background_size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-base_size/2-1, -background_size, -background_size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-base_size/2-1, background_size, -background_size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-base_size/2-1, background_size, background_size);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawGrid() {

	float i;

	glPushMatrix();

	glColor3f(0, 1, 1);
	glTranslatef(0, 0, 0);
	glRotatef(leftRight_rotation, 0, 1, 0);
	glRotatef(upDown_x, 1, 0, 0);
	glRotatef(upDown_z, 0, 0, 1);

	// glBindTexture(GL_TEXTURE_2D, textureID);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glColor3f(0.7, 0.6, 0.9);
	for (i = -N / 2; i <= N / 2; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(i, N / 2, -N / 2);
		glVertex3f(i, -N / 2, -N / 2);
		glEnd();
	}

	for (i = -N / 2; i <= N / 2; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(N / 2, i, -N / 2);
		glVertex3f(-N / 2, i, -N / 2);
		glEnd();
	}

	for (i = -N / 2; i <= N / 2; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(-N / 2, N / 2, i);
		glVertex3f(-N / 2, -N / 2, i);
		glEnd();
	}

	for (i = -N / 2; i <= N / 2; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(-N / 2, i, N / 2);
		glVertex3f(-N / 2, i, -N / 2);
		glEnd();
	}


	glColor3f(0.9, 0.9, 0.6);
	for (i = -N / 2; i <= N / 2; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(i, -N / 2, -N / 2);
		glVertex3f(i, -N / 2, N / 2);
		glEnd();
	}

	for (i = -N / 2; i <= N / 2; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(N / 2, -N / 2, i);
		glVertex3f(-N / 2, -N / 2, i);
		glEnd();
	}
}

GLuint loadTexture(const char* filename) {
    GLuint textureID = SOIL_load_OGL_texture(
        filename,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (textureID == 0) {
        throw std::runtime_error("Texture loading failed: " + std::string(SOIL_last_result()));
    }

    return textureID;
}

void update_game(int*** new_base, int base_size);

int main_display(int argc, char** argv);

#endif