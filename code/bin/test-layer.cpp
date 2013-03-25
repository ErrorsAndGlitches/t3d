#include <GL/glut.h>
#include <iostream>
#include "Layer.h"

using std::cout;
using std::endl;

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;

const int numSuperBlockTypes = 5;
int blockType = 0;
Layer<3, 3> layer;

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void initGL(int Width, int Height)
{
	//
	glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	

  glMatrixMode(GL_MODELVIEW);
}

/**
 * @brief reshape callback
 */
void reshapeCallback(int w, int h) 
{
}

/**
 * @brief draw callback
 */
void drawCallback() 
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
  glLoadIdentity();				// Reset The View
	gluLookAt(4, -10, 4, 
					  0, 0, 0,
						0, 0, 1);

	layer.Drawable::draw();

	// draw some axis
	glBegin(GL_LINES);
		// x axis
		glColor4f(1, 0, 0, 1);
		glVertex3f(-100, 0, 0);
		glVertex3f(100, 0, 0);
		// y axis
		glColor4f(0, 1, 0, 1);
		glVertex3f(0, -100, 0);
		glVertex3f(0, 100, 0);
		// z axis
		glColor4f(0, 0, 1, 1);
		glVertex3f(0, 0, -100);
		glVertex3f(0, 0, 100);
	glEnd();

	glutSwapBuffers(); // make it all visible
} 

/**
 * @brief idle callback
 */
void idleCallback()
{
	glutPostRedisplay(); // redraw everything (since bullets move)
}

void processNormalKeysCallback(unsigned char key, int xx, int yy)
{
	unsigned char saveKey = key;
	key -= '0';
	switch (key) {
		case 0: 
			layer.flipPosStatus(key % 3, key / 3);
			break;
		case 1:
			layer.flipPosStatus(key % 3, key / 3);
			break;
		case 2:
			layer.flipPosStatus(key % 3, key / 3);
			break;
		case 3:
			layer.flipPosStatus(key % 3, key / 3);
			break;
		case 4:
			layer.flipPosStatus(key % 3, key / 3);
			break;
		case 5:
			layer.flipPosStatus(key % 3, key / 3);
			break;
		case 6:
			layer.flipPosStatus(key % 3, key / 3);
			break;
		case 7:
			layer.flipPosStatus(key % 3, key / 3);
			break;
		case 8:
			layer.flipPosStatus(key % 3, key / 3);
			break;
		default:
			std::cout << "You entered an unmapped key: (" << saveKey << ")" << endl;
			break;
	}
}

int main(int argc, char **argv) 
{
	std::cout << 
		"\n"
		"-----------------------------------------------------------------------\n"
  	"Tetris 3D Testing Program:\n"
		" - 0..8 add/remove block at the position\n"
		"-----------------------------------------------------------------------" << endl;
	glutInit(&argc, argv); // initialize glut state
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Super Block Test");

	// register callbacks
	glutReshapeFunc(reshapeCallback); // window reshape callback
	glutDisplayFunc(drawCallback); // (re)display callback
	glutIdleFunc(idleCallback); // incremental update 

	glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
	glutKeyboardFunc(processNormalKeysCallback); // process standard key clicks

	initGL(WINDOW_WIDTH, WINDOW_HEIGHT);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
