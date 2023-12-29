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

//sudo apt-get install libsoil-dev
//sudo apt-get install freeglut3-dev

//compiler avec: g++ display-game.cpp -o tetris3d.exe -lGL -lGLU -lglut -lSOIL

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

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(zoom, 2, 0, 0, 0, 0, 0, 1, 0);

	drawGrid();

	drawFloor(floorID);

	drawBackground(fujisanID);

    for (int j = 0; j < base_size; j++)
	{
		for (int k = 0; k < base_size; k++)
		{
			for (int l = 0; l < base_size; l++)
			{
				if (base[j][k][l] == 1)
				{
					glPushMatrix();

					drawCube(j, k, l, 1, cobblestoneID);

					glPopMatrix();
				}
			}
		}
	}

	glPopMatrix();

	glutSwapBuffers();
	glFlush();

}

void normal_keys(unsigned char key, int x, int y) {
	if (key == 27) exit(0);
}

void special_keys(int keys, int x, int y) {
	int moires = 0;

	if (leftRight_rotation < 0)
		moires = leftRight_rotation % 360 + 360;
	else
		moires = leftRight_rotation % 360;

	int undox = movex;
	int undoz = movez;

	switch (keys) {
	case GLUT_KEY_F1:// F1 toggles fullscreen mode
		fullscreen = !fullscreen;
		if (fullscreen) glutFullScreen();
		else glutReshapeWindow(500, 500);
		break;

	case GLUT_KEY_LEFT:
		if (!stop) {
			if (moires <= 45 || moires > 315)
			{
				if (movez < d / 2)
					movez++;
			}
			else if (moires > 135 && moires <= 225)
			{
				if (movez > -d / 2 - 2)
					movez--;
			}
			else if (moires > 45 && moires <= 135)
			{
				if (movex > -d / 2 - 2)
					movex--;
			}
			else if (moires > 225 && moires <= 315)
			{
				if (movex < d / 2)
					movex++;
			}
		}

		break;

	case GLUT_KEY_RIGHT:
		if (!stop) {
			if (moires <= 45 || moires > 315)
			{
				if (movez > -d / 2 - 2)
					movez--;
			}
			else if (moires > 135 && moires <= 225)
			{
				if (movez < d / 2)
					movez++;
			}
			else if (moires > 45 && moires <= 135)
			{
				if (movex < d / 2)
					movex++;
			}
			else if (moires > 225 && moires <= 315)
			{
				if (movex > -d / 2 - 2)
					movex--;
			}
		}
		break;

	case GLUT_KEY_UP:
		if (!stop) {
			if (moires <= 45 || moires > 315)
			{
				if (movex > -d / 2 - 2)
					movex--;
			}
			else if (moires > 135 && moires <= 225)
			{
				if (movex < d / 2)
					movex++;
			}
			else if (moires > 45 && moires <= 135)
			{
				if (movez > -d / 2 - 2)
					movez--;
			}
			else if (moires > 225 && moires <= 315)
			{
				if (movez < d / 2)
					movez++;
			}
		}
		break;

	case GLUT_KEY_DOWN:
		if (!stop) {
			if (moires <= 45 || moires > 315)
			{
				if (movex < d / 2)
					movex++;
			}
			else if (moires > 135 && moires <= 225)
			{
				if (movex > -d / 2 - 2)
					movex--;
			}
			else if (moires > 45 && moires <= 135)
			{
				if (movez < d / 2)
					movez++;
			}
			else if (moires > 225 && moires <= 315)
			{
				if (movez > -d / 2 - 2)
					movez--;
			}
		}
		break;

	default:
		break;
	}
}

/*void mouse_button(int button, int state, int x, int y) {
	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
		drawshape = (drawshape+1)%3;
		display();
	}
}*/

void keyboard(unsigned char key, int mousePositionX, int mousePositionY) {
    int moires = 0;

	if (leftRight_rotation < 0)
		moires = leftRight_rotation % 360 + 360;
	else
		moires = leftRight_rotation % 360;


	switch (key)
	{
	case 's':
		if (stop)
			stop = false;
		else
			stop = true;

		break;

	case 'i':
		if (moires <= 45 || moires > 315)
		{
			upDown_z += r_speed;
		}
		else if (moires > 135 && moires <= 225)
		{
			upDown_z -= r_speed;
		}
		else if (moires > 45 && moires <= 135)
		{
			upDown_x -= r_speed;
		}
		else if (moires > 225 && moires <= 315)
		{
			upDown_x += r_speed;
		}

		break;

	case 'k':
		if (moires <= 45 || moires > 315)
		{
			upDown_z -= r_speed;
		}
		else if (moires > 135 && moires <= 225)
		{
			upDown_z += r_speed;
		}
		else if (moires > 45 && moires <= 135)
		{
			upDown_x += r_speed;
		}
		else if (moires > 225 && moires <= 315)
		{
			upDown_x -= r_speed;
		}

		break;

	case 'f':
		if (zoom > 2)
			zoom -= 2;
		break;

	case 'd':
		if (zoom < 100)
			zoom += 2;
		break;

	case 'j':
		leftRight_rotation += r_speed;
		break;

	case 'l':
		leftRight_rotation -= r_speed;
		break;

	// case 'x':
	// 	if (!stop)
	// 		shp.rotateShape_x();
	// 	break;

	// case 'c':
	// 	if (!stop)
	// 		shp.rotateShape_y();
	// 	break;

	// case 'v':
	// 	if (!stop)
	// 		shp.rotateShape_z();
	// 	break;

	case KEY_ESCAPE:
		exit(0);
		break;

	default:
		break;
	}
}

void initialize()
{
	cobblestoneID = loadTexture("../../textures/cobblestone.png");
	floorID = loadTexture("../../textures/floor.png");
	fujisanID = loadTexture("../../textures/fujisan.png");

	// select projection matrix
	glMatrixMode(GL_PROJECTION);

	// set the viewport
	glViewport(0, 0, win.width, win.height);

	// set matrix mode
	glMatrixMode(GL_PROJECTION);

	// reset projection matrix
	glLoadIdentity();
	GLfloat aspect = (GLfloat)win.width / win.height;

	// set up a perspective projection matrix
	gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);

	// specify which matrix is the current matrix
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);

	// specify the clear value for the depth buffer
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_2D);

	// specify implementation-specific hints
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	GLfloat material_ambient[] = { 0.7, 0.7, 0.7, 1.0 };  // Ambient material color (RGBA)
	GLfloat material_diffuse[] = { 0.9, 0.9, 0.9, 1.0 };  // Diffuse material color (RGBA)
	GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // Specular material color (RGBA)
	GLfloat shininess = 10.0;  // Shininess parameter
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

int main(int argc, char** argv) {
	//set window values
	win.width = 640;
	win.height = 480;
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 500.0f;


    //initalize base with zeros
	for (int i = 0; i < d; i++)
	{
		for (int j = 0; j < d; j++)
		{
			for (int k = 0; k < d; k++)
			{
				base[i][j][k] = 0;
			}
		}
	}

    base[0][0][0] = 1;
    base[0][0][1] = 1;
    base[0][1][0] = 1;

	glutInit(&argc, argv);// Initialize glut
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);// Display Mode
	glutInitWindowSize(win.width, win.height);// Set the window size
	glutCreateWindow("Tetris 3D");// Create the window with given title
	glutDisplayFunc(display);// Set the display function
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);// Set the normal keyboard function
	glutSpecialFunc(special_keys);// Set the special keyboard function
    //glutMouseFunc(mouse_button);// Set the mouse button function
	initialize();
    
    glutMainLoop();// Initialize main loop
	
	return 0;
}