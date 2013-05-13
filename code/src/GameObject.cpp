#include "GameObject.h"
#ifdef _WIN32
	#include <windows.h>
#endif
#include "GL/gl.h"

void GameObject::updateRelaPos(float xRel, float yRel, float zRel)
{
	pos.updateRelaPos(xRel, yRel, zRel);
}

void GameObject::updateRelaPos(const Vector& p)
{
	pos += p;
}

void GameObject::setPos(const Vector& v) 
{ 
	pos = v; 
}

Vector GameObject::getPos() const 
{ 
	return pos; 
}
