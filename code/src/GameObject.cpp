#include "GameObject.h"

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
