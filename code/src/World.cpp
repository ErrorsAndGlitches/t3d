/*http://www.opengl.org/archives/resources/faq/technical/viewing.htm*/
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
#include "Defs.h"
#include "TextureService.h"



const float NEAR_FIELD = 1;
const float FAR_FIELD= 100; 

World::World()
{
	length = DEFAULT_SUBARENA_LENGTH;
	height = DEFAULT_SUBARENA_HEIGHT;


	aspectRatio = 1; // default aspect ratio (will be changed)
	init();
}

void World::init()
{
	xDragStart = 0;
	yDragStart = 0;
	isDragging = false;

	xRotation = 0;
	zRotation = 0;
	xRotationDelta = 0;
	zRotationDelta = 0;
	orientaion = 1;
}

void World::reset()
{

	arena->reset();
	init();
}

void World::setArena(Arena* arena)
{
	this->arena = arena;
}

void World::draw(void)
{
	setUpCamera();
			

	glBindTexture(GL_TEXTURE_2D, TextureService::getTextureServiceInstance()->getTexture(TextureService::BACKGROUND));
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glBegin(GL_QUADS);
			
		glTexCoord2i(0, 0); glVertex3f(-20, 70, -20);
		glTexCoord2i(1, 0); glVertex3f(20,	70, -20);
		glTexCoord2i(1, 1); glVertex3f(20,	70, 20);
		glTexCoord2i(0, 1); glVertex3f(-20, 70, 20);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Rotate the arena
	glRotatef(xRotation + xRotationDelta, 1, 0, 0);
	glRotatef(zRotation + zRotationDelta, 0, 0, 1);
	glPushMatrix();
		//Move to center
		glTranslatef((-length / 2.0) , (-length / 2.0), 0);
		arena->draw();
	glPopMatrix();
	//plateform.draw();
  
}

void World::setAspectRatio(float ratio)
{
	aspectRatio = ratio;
}

void World::setUpCamera()
{
	//From the openGl tutorial on camera motion at www.opengl.org/archives/resources/faq/technical/viewing.htm
	float clearing = 1;

	GLdouble left =  -(length * clearing);
	GLdouble right = (length * clearing);
	GLdouble bottom = -(height * clearing);
	GLdouble top = (height * clearing);
	if ( aspectRatio < 1.0 ) { // window taller than wide
		bottom /= aspectRatio;
		top /= aspectRatio;
	} else {
		left *= aspectRatio;
		right *= aspectRatio;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, NEAR_FIELD, FAR_FIELD);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	int cameraY = bottom * 2;
	gluLookAt (0., cameraY, 0,
                0, 0, 0,
                0.0, 0, 1.0);
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
