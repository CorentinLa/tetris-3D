#include"display-game.hpp"
#include<thread>

//sudo apt-get install libsoil-dev
//sudo apt-get install freeglut3-dev

//g++ -c src/display/3d/display-game.cpp -o obj/display-game.o -lGL -lGLU -lglut -lSOIL



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
bool gameOver = false;
const int base_size = 15;
Game* onGoingGame;

bool stop = true;

void *font = GLUT_BITMAP_HELVETICA_18;

int base[base_size][base_size][base_size];

GLuint cobblestoneID;
GLuint goldID;
GLuint floorID;
GLuint ironID;
glutWindow win;

void update_game(int*** new_base, int base_s) {
	for (int i = 0; i < base_s; ++i) {
		for (int j = 0; j < base_s;  ++j) {
			for (int k = 0; k < base_s; ++k) {
				base[i][j][k] = new_base[i][j][k];
			}								
		}					
	}
}

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


	// show fps
	static int frame = 0, time, timebase = 0;
	static char buffer[256];

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(buffer, "FPS:%4.2f",
			frame*1000.0 / (time - timebase));
			glutSetWindowTitle(buffer);
		timebase = time;
		frame = 0;
	}

	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(zoom, 2, 0, 0, 0, 0, 0, 1, 0);

	drawGrid();

	// write the score

	glColor3f(1, 1, 1);
	glRasterPos3f(-N / 2, N / 2, -N / 2);
	std::string score = "Score: " + std::to_string(onGoingGame->getScore());
	for (int i = 0; i < score.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[i]);
	}

	drawFloor(floorID);

    for (int j = 0; j < base_size; j++)
	{
		for (int k = 0; k < base_size; k++)
		{
			for (int l = 0; l < base_size; l++)
			{
				if (base[j][k][l] == 2)
				{
					glPushMatrix();

					drawCube(j, l-base_size/2, k, 1, ironID);

					glPopMatrix();
				}
				else if (base[j][k][l] == 1)
					{
						glPushMatrix();

						drawCube(j, l-base_size/2, k, 1, goldID);

						glPopMatrix();
					}
				else if (base[j][k][l] == 3)
				{
					glPushMatrix();

					drawCube(j, l-base_size/2, k, 1, cobblestoneID);

					glPopMatrix();
				}
			}
		}
	}

	

	glPopMatrix();

	glutSwapBuffers();
	glFlush();

}

void initGame(Game* startedGame) {
	onGoingGame = startedGame;
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
	case 'q': // Z
		if (onGoingGame->currentPieceMovable('Y')) {
			onGoingGame->destroyCurrentPiece();
			onGoingGame->moveCurrentPiece('Y');
			onGoingGame->constructCurrentPiece();
		}
		break;
	case 'd': // S
		if (onGoingGame->currentPieceMovable('y')) {
			onGoingGame->destroyCurrentPiece();
			onGoingGame->moveCurrentPiece('y');
			onGoingGame->constructCurrentPiece();
		}
		break;
	case 'z': // Q
		if (onGoingGame->currentPieceMovable('x')) {
			onGoingGame->destroyCurrentPiece();
			onGoingGame->moveCurrentPiece('x');
			onGoingGame->constructCurrentPiece();
		}
		break;
	case 's': // D
		if (onGoingGame->currentPieceMovable('X')) {
			onGoingGame->destroyCurrentPiece();
			onGoingGame->moveCurrentPiece('X');
			onGoingGame->constructCurrentPiece();
		}
		break;
	case 'w': 
		if (onGoingGame->currentPieceMovable('z')) {
			onGoingGame->destroyCurrentPiece();
			onGoingGame->moveCurrentPiece('z');
			onGoingGame->constructCurrentPiece();
		}
		break;
	case 'a':
		if(onGoingGame->currentPieceRotatable('z', 'p')) {
		onGoingGame->destroyCurrentPiece();
		onGoingGame->rotateCurrentPiece('z', 'p');
		onGoingGame->constructCurrentPiece();
		}
		break;
	case 'e':
		if(onGoingGame->currentPieceRotatable('z', 'n')) {
		onGoingGame->destroyCurrentPiece();
		onGoingGame->rotateCurrentPiece('z', 'n');
		onGoingGame->constructCurrentPiece();
		}
		break;
	// case 'r':
	// 	if(onGoingGame->currentPieceRotatable('x', 'p')) {
	// 	onGoingGame->destroyCurrentPiece();
	// 	onGoingGame->rotateCurrentPiece('x', 'p');
	// 	onGoingGame->constructCurrentPiece();
	// 	}
	// 	break;
	// case 'f':
	// 	if(onGoingGame->currentPieceRotatable('x', 'n')) {
	// 	onGoingGame->destroyCurrentPiece();
	// 	onGoingGame->rotateCurrentPiece('x', 'n');
	// 	onGoingGame->constructCurrentPiece();
	// 	}
	// 	break;
	case 'u':
		if(onGoingGame->currentPieceRotatable('y', 'p')) {
		onGoingGame->destroyCurrentPiece();
		onGoingGame->rotateCurrentPiece('y', 'p');
		onGoingGame->constructCurrentPiece();
		glutPostRedisplay();
		}
		break;
	case 'o':
		if(onGoingGame->currentPieceRotatable('y', 'n')) {
		onGoingGame->destroyCurrentPiece();
		onGoingGame->rotateCurrentPiece('y', 'n');
		onGoingGame->constructCurrentPiece();
		glutPostRedisplay();
		}
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

	case 'h':
		if (zoom > 2)
			zoom -= 2;
		break;

	case 'g':
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
		Board board = onGoingGame->getBoard();
        int*** boardMat = board.getBoardMat();
        int width = board.getWidth(); 
        update_game(boardMat, width); 
	glutPostRedisplay();
}

void initialize()
{
	cobblestoneID = loadTexture("./resources/textures/cobblestone.png");
	floorID = loadTexture("./resources/textures/floor.png");
	goldID = loadTexture("./resources/textures/gold.png");
	ironID = loadTexture("./resources/textures/iron.png");

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

int main_display(int argc, char** argv) {

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