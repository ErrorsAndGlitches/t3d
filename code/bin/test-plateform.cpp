#include <iostream>                     // C++ I/O

#include <GL/glut.h>                    // GLUT
#include <GL/glu.h>                     // GLU
#include <GL/gl.h>                      // OpenGL

#include "World.h"
using namespace std;                    // make std accessible

//-----------------------------------------------------------------------
// Global data
//-----------------------------------------------------------------------
World world(7);



//-----------------------------------------------------------------------
//  Callbacks
//-----------------------------------------------------------------------

//----------------------------------------------------------------------
// Reshape callback
//
// Window size has been set/changed to w by h pixels.
//----------------------------------------------------------------------
void myReshape(int w, int h) 
{
	world.setAspectRatio(float(w)/float(h)); // set new aspect ratio
	glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}


void myDisplay(void) {                          // display callback
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);               // clear the window
	glClearColor(0.75, 0.5, 0.75, 1.0);           // background is gray
    
	glLoadIdentity();
	world.draw();
	
	glutSwapBuffers();                          // swap buffers
}

//Used a glutTimerFUnc based update system because it was much smoother
//and consistant than idle event timer, and seemed to work fine without 
//any refresh rate issues
void update(int step) 
{

	glutPostRedisplay(); // redraw everything (since camera may move)
	glutTimerFunc(30, update, 1);

}

void mouseMove(int xx, int yy)  { world.mouseMove(xx, yy); }
void mouseButton(int button, int state, int xx, int yy)  { world.mouseButton(button, state, xx, yy); }


                                               
void myKeyboard(unsigned char c, int x, int y) {
    switch (c) {                                // c is the key that is hit
        case 'q':                               // 'q' means quit
            exit(0);
            break;
        default:
            cout << "Hit q to quit.  All other characters ignored" << endl;
            break;
    }
}

//-----------------------------------------------------------------------
//  Main program
//      This does all the set up for the program.  It creates the game
//      and then passes control to glut.
//-----------------------------------------------------------------------

int main(int argc, char** argv)
{


    glutInit(&argc, argv);                      // OpenGL initializations
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 400);
	glutCreateWindow("3D TETRIS");
    glutDisplayFunc(myDisplay);                 // setup callbacks
    glutReshapeFunc(myReshape);
	glutTimerFunc(30, update, 1);
    


	glutMouseFunc(mouseButton);			 // process mouse button push/release
	glutMotionFunc(mouseMove);			 // process mouse dragging 
    glutKeyboardFunc(myKeyboard);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();                             // start it running
    
	return 0;                                   // ANSI C expects this
}