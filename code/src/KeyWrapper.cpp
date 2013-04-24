#include "KeyWrapper.h"


KeyWrapper::KeyWrapper(int key)
{
	keyValue.specialKey = key;
	isSpecial = true;
}

KeyWrapper::KeyWrapper(unsigned char key)
{
	keyValue.normalKey = key;
	isSpecial = false;
}


bool KeyWrapper::equals(int key)
{
	return isSpecial && (key == keyValue.specialKey);
}

bool KeyWrapper::equals(unsigned char key)
{
	return (!isSpecial) && (key == keyValue.normalKey);
}
