#include "Block.h"

void Block::draw(const float *const color) const 
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		glColor3fv(color);
		drawColoredBlock();
		glColor3fv(WHITE); // so we don't have a tint for future texture draws
	glPopMatrix();
}

void Block::draw(const GLuint texId) const 
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);

		// tell opengl which texture we want to use
		glBindTexture(GL_TEXTURE_2D, texId);
		glEnable(GL_TEXTURE_2D);
			drawTexturedBlock();
		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void Block::drawColoredBlock() const
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

void Block::drawTexturedBlock() const
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
