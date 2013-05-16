
#include <iostream>
#include <GL/glut.h>
#include "World.h"
#include "Arena.h"
#include "InputComponent.h"
#include "Player.h"
#include "Defs.h"


using std::cout;
using std::endl;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 400;

World world(World::NetworkPlayerType::HOST);
InputComponent ic1;

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void initGL(int Width, int Height)
{

  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix

  glMatrixMode(GL_MODELVIEW);
}

/**
 * @brief reshape callback
 */
void reshapeCallback(int w, int h) 
{
	world.setAspectRatio(float(w)/float(h)); // set new aspect ratio
	glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}

/**
 * @brief draw callback
 */
void drawCallback() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);               // clear the window
	glClearColor(0, 0, 0, 1.0);           // background is gray
    
	glLoadIdentity();
	world.draw();

	glutSwapBuffers(); // make it all visible
} 

/**
 * @brief idle callback
 */
void idleCallback()
{
	world.updateNetworkPlayer();
	glutPostRedisplay(); // redraw everything (since bullets move)
}

void processNormalKeysCallback(unsigned char key, int xx, int yy)
{
	if (key == 'R') world.reset();
	if (key == 'p' || key == 'P') {
		world.toggleMusic();
	}
	ic1.processKeyboardInput(key);
}

void processSpecialKeysCallback(int key, int x, int y)
{
	ic1.processKeyboardInput(key);
}

void mouseMove(int xx, int yy)  { world.mouseMove(xx, yy); }
void mouseButton(int button, int state, int xx, int yy)  { world.mouseButton(button, state, xx, yy); }

int main(int argc, char **argv) 
{
	std::cout << 
		"\n"
		"-----------------------------------------------------------------------\n"
  	"Tetris 3D Testing Program:\n"
		" - a/d/w:  rotate about x/y/z-axis\n"
		" - arrow keys: move the superblock in the x-y plane\n"
		" - s: move the superblock down\n"
		" - SPACE: insert superblock and switch to the next random tetris block\n"
		" - R: Reset the game\n"
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
	glutMouseFunc(mouseButton);			 // process mouse button push/release
	glutMotionFunc(mouseMove);			 // process mouse dragging 
	glutIgnoreKeyRepeat(1);				// ignore key repeat when holding key down
	glutKeyboardFunc(processNormalKeysCallback); // process standard key clicks
	glutSpecialFunc(processSpecialKeysCallback);

	initGL(WINDOW_WIDTH, WINDOW_HEIGHT);

	//Assign arena to world
	Arena a;
	world.setArena(&a);

	// set up player bindings
	Player player1; KeyMapping map1(KeyMapping::MULTI_PLAYER_A);
	ic1.bindPlayerToMapping(&player1, map1);
	a.assignToArena(&player1, Arena::TOP_ARENA);

	world.startNetworkGame();

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
