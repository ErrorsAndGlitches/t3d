#include <iostream>  

#ifdef _WIN32
# 	include <windows.h>
#else
# 	include <cmath>
#endif
#include <GL/glut.h>                    // GLUT
#include <GL/glu.h>                     // GLU
#include <GL/gl.h>                      // OpenGL

#include "World.h"


const float FOV = 35.0;
const float NEAR_FIELD = 0.1;
const float FAR_FIELD= 200.0; 
const float CLEARING = 1.25;

World::World(int dimension)
{
	this->dimension = dimension;

	aspectRatio = 1; // default aspect ratio (will be changed)
	xDragStart = 0;
	yDragStart = 0;
	isDragging = false;

	xRotation = 0;
	zRotation = 0;
	xRotationDelta = 0;
	zRotationDelta = 0;
	orientaion = 1;

	plateform = Platform(dimension);

}


void World::draw(void)
{
	setUpCamera();

	//Rotate the arena
	glRotatef(xRotation + xRotationDelta, 1, 0, 0);
	glRotatef(zRotation + zRotationDelta, 0, 0, 1);
	plateform.draw();
  
}

void World::setAspectRatio(float ratio)
{
	aspectRatio = ratio;
}

void World::setUpCamera()
{
	float clearing = 1.25;

	gluLookAt(
		0,		-(dimension * clearing),	(dimension * clearing),
		0,		0.0,						0,
		0.0,	0.0,						1.0);

	glMatrixMode(GL_PROJECTION); // projection matrix is active
	glLoadIdentity(); // reset the projection
	gluPerspective(FOV, aspectRatio, NEAR_FIELD, FAR_FIELD); // perspective transformation
	glMatrixMode(GL_MODELVIEW); // return to modelview mode
}

void World::mouseMove(int xx, int yy) 
{
	float dragSpeed = .5;
	
	float rotSum = ((int)abs(floorf(xRotation + xRotationDelta)) % 360 );

	//If  upside down, reset the drag start position, the orientation, and 
	//solidify the rotation about the z axis. Only exexutes upon orientaiton
	//change.
	if ((rotSum > 90) && ( rotSum < 270) && (orientaion == 1)){
		orientaion = -1;
		xDragStart = xx;
		zRotation = zRotation + zRotationDelta;

	} 
	//If rightside up, reset the drag start position, the orientation, and 
	//solidify the rotation about the z axis. Only executes upon orientation change
	else if ( (!(rotSum > 90) && ( rotSum < 270)) && (orientaion == -1)) {
		orientaion = 1;
		xDragStart = xx;
		zRotation = zRotation + zRotationDelta;
	}

	//We calculate how much we should rotate the world by
	if (isDragging) {
		zRotationDelta = (xx - xDragStart) * dragSpeed * orientaion;
		xRotationDelta = (yy - yDragStart) * dragSpeed;
	}
}
void World::mouseButton(int button, int state, int xx, int yy)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			isDragging = true;
			xDragStart = xx;
			yDragStart = yy;
		}

		//This will solidify the world rotation
		else 
		{
			isDragging = false;
			xRotation = xRotation + xRotationDelta;
			zRotation = zRotation + zRotationDelta;
			xRotationDelta = 0;
			zRotationDelta = 0;
		}
	}
}
