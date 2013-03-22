#include "Block.h"

void Block::drawColoredGameObject()
{
	// all the quads begin in the lower left corner and are drawn in an
	// anti-clockwise fashion
	glBegin(GL_QUADS);
		// y = 0 plane
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);
		// x = 1 plane
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		// y = 1 plane
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		// x = 0 plane
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 1.0f);
		// z = 0 plane
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		// z = 1 plane
		glVertex3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 1.0f);
	glEnd();
}

void Block::drawTexturedGameObject()
{
	glBegin(GL_QUADS);
		// y = 0 plane
		glTexCoord2i(0, 0); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2i(1, 0); glVertex3f(1.0f, 0.0f, 0.0f);
		glTexCoord2i(1, 1); glVertex3f(1.0f, 0.0f, 1.0f);
		glTexCoord2i(0, 1); glVertex3f(0.0f, 0.0f, 1.0f);
		// x = 1 plane
		glTexCoord2i(0, 0); glVertex3f(1.0f, 0.0f, 0.0f);
		glTexCoord2i(1, 0); glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2i(1, 1); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2i(0, 1); glVertex3f(1.0f, 0.0f, 1.0f);
		// y = 1 plane
		glTexCoord2i(0, 0); glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2i(1, 0); glVertex3f(0.0f, 1.0f, 0.0f);
		glTexCoord2i(1, 1); glVertex3f(0.0f, 1.0f, 1.0f);
		glTexCoord2i(0, 1); glVertex3f(1.0f, 1.0f, 1.0f);
		// x = 0 plane
		glTexCoord2i(0, 0); glVertex3f(0.0f, 1.0f, 0.0f);
		glTexCoord2i(1, 0); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2i(1, 1); glVertex3f(0.0f, 0.0f, 1.0f);
		glTexCoord2i(0, 1); glVertex3f(0.0f, 1.0f, 1.0f);
		// z = 0 plane
		glTexCoord2i(0, 0); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2i(1, 0); glVertex3f(0.0f, 1.0f, 0.0f);
		glTexCoord2i(1, 1); glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2i(0, 1); glVertex3f(1.0f, 0.0f, 0.0f);
		// z = 1 plane
		glTexCoord2i(0, 0); glVertex3f(0.0f, 0.0f, 1.0f);
		glTexCoord2i(1, 0); glVertex3f(1.0f, 0.0f, 1.0f);
		glTexCoord2i(1, 1); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2i(0, 1); glVertex3f(0.0f, 1.0f, 1.0f);
	glEnd();
}
