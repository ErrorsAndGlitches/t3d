#include "GameObject.h"
#include "GL/gl.h"

inline void GameObject::updateRelaPos(float xRel, float yRel, float zRel)
{
	pos.updateRelaPos(xRel, yRel, zRel);
}

inline void GameObject::updateRelaPos(const Vector& p)
{
	pos += p;
}

inline void GameObject::setPos(const Vector& v) 
{ 
	pos = v; 
}

inline Vector GameObject::getPos() const 
{ 
	return pos; 
}

inline void GameObject::draw() const
{
	draw(DEFAULT_COLOR);
}

void GameObject::draw(const float *const color) const
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		glColor3fv(color);
		drawColoredGameObject();
		glColor3fv(WHITE); // so we don't have a tint for future texture draws
	glPopMatrix();
}

void GameObject::draw(const GLuint texId) const
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);

		// tell opengl which texture we want to use
		glBindTexture(GL_TEXTURE_2D, texId);
		glEnable(GL_TEXTURE_2D);
			drawTexturedGameObject();
		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
