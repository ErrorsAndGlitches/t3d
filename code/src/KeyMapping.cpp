#include "KeyMapping.h"
#include "gl/glut.h"

KeyMapping::KeyMapping(DefaultMapping mapping)
{
	setDefaultMapping(mapping);
}

void KeyMapping::setActionKeyMapping(PlayerCommand::Action action, int keyMapping)
{
	mappings[action] = KeyWrapper(keyMapping);
}

void KeyMapping::setActionKeyMapping(PlayerCommand::Action action, unsigned char keyMapping)
{
	mappings[action] = KeyWrapper(keyMapping);
}

void KeyMapping::setDefaultMapping(DefaultMapping mapping)
{
	switch (mapping)
	{
	case KeyMapping::SINGLE_PLAYER:
		mappings[PlayerCommand::ROTATE_X] = KeyWrapper((unsigned char)'a'); 
		mappings[PlayerCommand::ROTATE_Y] = KeyWrapper((unsigned char)'d');
		mappings[PlayerCommand::ROTATE_Z] = KeyWrapper((unsigned char) 'w');
		mappings[PlayerCommand::MOVE_X_POS] = KeyWrapper(GLUT_KEY_LEFT); 
		mappings[PlayerCommand::MOVE_X_NEG] = KeyWrapper(GLUT_KEY_RIGHT); 
		mappings[PlayerCommand::MOVE_Y_POS] = KeyWrapper(GLUT_KEY_UP); 
		mappings[PlayerCommand::MOVE_Y_NEG] = KeyWrapper(GLUT_KEY_DOWN);
		mappings[PlayerCommand::DROP_BLOCK] = KeyWrapper((unsigned char)' '); 
		break;
	case KeyMapping::MULTI_PLAYER_A:
		mappings[PlayerCommand::ROTATE_X] = KeyWrapper((unsigned char)'z'); 
		mappings[PlayerCommand::ROTATE_Y] = KeyWrapper((unsigned char)'x');
		mappings[PlayerCommand::ROTATE_Z] = KeyWrapper((unsigned char) 'c');
		mappings[PlayerCommand::MOVE_X_POS] = KeyWrapper((unsigned char) 'd'); 
		mappings[PlayerCommand::MOVE_X_NEG] = KeyWrapper((unsigned char) 'a'); 
		mappings[PlayerCommand::MOVE_Y_POS] = KeyWrapper((unsigned char) 'w'); 
		mappings[PlayerCommand::MOVE_Y_NEG] = KeyWrapper((unsigned char) 's');
		mappings[PlayerCommand::DROP_BLOCK] = KeyWrapper((unsigned char)' '); 
		break;
	case KeyMapping::MULTI_PLAYER_B:
		mappings[PlayerCommand::ROTATE_X] = KeyWrapper((unsigned char)','); 
		mappings[PlayerCommand::ROTATE_Y] = KeyWrapper((unsigned char)'.');
		mappings[PlayerCommand::ROTATE_Z] = KeyWrapper((unsigned char) '/');
		mappings[PlayerCommand::MOVE_X_POS] = KeyWrapper((unsigned char) '\''); 
		mappings[PlayerCommand::MOVE_X_NEG] = KeyWrapper((unsigned char) 'l'); 
		mappings[PlayerCommand::MOVE_Y_POS] = KeyWrapper((unsigned char) 'p'); 
		mappings[PlayerCommand::MOVE_Y_NEG] = KeyWrapper((unsigned char) ';');
		mappings[PlayerCommand::DROP_BLOCK] = KeyWrapper((unsigned char)'\r'); 
		break;
	default:
		break;
	}
}

KeyWrapper KeyMapping::getActionKeyMapping(PlayerCommand::Action action)
{
	return mappings[action];
}

