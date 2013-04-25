#include <GL/glut.h>
#include <iostream>
#include "SuperBlockFactory.h"

using std::cout;
using std::endl;

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;

float rotation = 0.0f;

SuperBlockFactory *sbFactory = SuperBlockFactory::getSuperBlockFactoryInstance();
SuperBlock *sb = sbFactory->getRandomSuperBlock();

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
//	rotation += 1;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
  glLoadIdentity();				// Reset The View
	gluLookAt(4, -10, 4, 
					  0, 0, 0,
						0, 0, 1);

//	glRotatef(90, 1, 0, 0); // rotate entire world

	sb->Drawable::draw();

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
	if ('x' == key)
		sb->rotateX();
	if ('y' == key)
		sb->rotateY();
	if ('z' == key)
		sb->rotateZ();
	if (' ' == key) {
		delete(sb);
		sb = sbFactory->getRandomSuperBlock();
	}
}

int main(int argc, char **argv) 
{
	std::cout << 
		"\n"
		"-----------------------------------------------------------------------\n"
  	"Tetris 3D Testing Program:\n"
		" - x rotate about x-axis\n"
		" - y rotate about y-axis\n"
		" - z rotate about z-axis\n"
		" - SPACE switch to the next random tetris block\n"
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
