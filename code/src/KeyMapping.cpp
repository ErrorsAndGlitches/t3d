#include "KeyMapping.h"

#ifdef _WIN32
# 	include "gl/glut.h"
#else
# 	include "GL/freeglut.h"
#endif

KeyMapping::KeyMapping(DefaultMapping mapping)
{
	setDefaultMapping(mapping);
}

void KeyMapping::setActionKeyMapping(Player::Action action, int keyMapping)
{
	mappings[action] = KeyWrapper(keyMapping);
}

void KeyMapping::setActionKeyMapping(Player::Action action, unsigned char keyMapping)
{
	mappings[action] = KeyWrapper(keyMapping);
}

void KeyMapping::setDefaultMapping(DefaultMapping mapping)
{
	switch (mapping)
	{
	case KeyMapping::SINGLE_PLAYER:
		mappings[Player::ROTATE_X] = KeyWrapper((unsigned char)'a'); 
		mappings[Player::ROTATE_Y] = KeyWrapper((unsigned char)'d');
		mappings[Player::ROTATE_Z] = KeyWrapper((unsigned char) 'w');
		mappings[Player::MOVE_X_POS] = KeyWrapper(GLUT_KEY_LEFT); 
		mappings[Player::MOVE_X_NEG] = KeyWrapper(GLUT_KEY_RIGHT); 
		mappings[Player::MOVE_Y_POS] = KeyWrapper(GLUT_KEY_UP); 
		mappings[Player::MOVE_Y_NEG] = KeyWrapper(GLUT_KEY_DOWN);
		mappings[Player::DROP_BLOCK] = KeyWrapper((unsigned char)' '); 
		break;
	case KeyMapping::MULTI_PLAYER_A:
		mappings[Player::ROTATE_X] = KeyWrapper((unsigned char)'z'); 
		mappings[Player::ROTATE_Y] = KeyWrapper((unsigned char)'x');
		mappings[Player::ROTATE_Z] = KeyWrapper((unsigned char) 'c');
		mappings[Player::MOVE_X_POS] = KeyWrapper((unsigned char) 'd'); 
		mappings[Player::MOVE_X_NEG] = KeyWrapper((unsigned char) 'a'); 
		mappings[Player::MOVE_Y_POS] = KeyWrapper((unsigned char) 'w'); 
		mappings[Player::MOVE_Y_NEG] = KeyWrapper((unsigned char) 's');
		mappings[Player::DROP_BLOCK] = KeyWrapper((unsigned char)' '); 
		break;
	case KeyMapping::MULTI_PLAYER_B:
		mappings[Player::ROTATE_X] = KeyWrapper((unsigned char)','); 
		mappings[Player::ROTATE_Y] = KeyWrapper((unsigned char)'.');
		mappings[Player::ROTATE_Z] = KeyWrapper((unsigned char) '/');
		mappings[Player::MOVE_X_POS] = KeyWrapper((unsigned char) '\''); 
		mappings[Player::MOVE_X_NEG] = KeyWrapper((unsigned char) 'l'); 
		mappings[Player::MOVE_Y_POS] = KeyWrapper((unsigned char) 'p'); 
		mappings[Player::MOVE_Y_NEG] = KeyWrapper((unsigned char) ';');
		mappings[Player::DROP_BLOCK] = KeyWrapper((unsigned char)'\r'); 
		break;
	default:
		break;
	}
}

KeyWrapper KeyMapping::getActionKeyMapping(Player::Action action)
{
	return mappings[action];
}

