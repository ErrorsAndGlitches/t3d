#include "Platform.h"



void Platform::draw()
{
	float thinkness = .01;	//How think the plateform will be
	float color = 0;
	float step = 1.0 / (dimension * dimension * 3);	//colloring pattern offsets

	glPushMatrix();
		glScalef(1, 1, thinkness);


		//Tile grid
		for (int row = 0; row < dimension; row++) {
			for (int col = 0; col < dimension; col++) {
				float colorR = color;  color+= step;
				float colorG = color;  color+= step;
				float colorB = color;  color+= step;

				glPushMatrix();
					glColor3f(colorR, colorG, colorB);
					glTranslatef(row + .5, col + .5, 0);
					glutSolidCube(1);
				glPopMatrix();
			}
		}
	glPopMatrix();

}
