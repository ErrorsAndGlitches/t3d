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
		
		mappings[PlayerCommand::TEST_Z_POS] = KeyWrapper((unsigned char)'1');
		mappings[PlayerCommand::TEST_Z_NEG] = KeyWrapper((unsigned char)'2');
		mappings[PlayerCommand::TEST_NEW_BLOCK] = KeyWrapper((unsigned char)'3');
		mappings[PlayerCommand::TEST_COMMIT_BLOCK] = KeyWrapper((unsigned char)'4');
		
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

		mappings[PlayerCommand::TEST_Z_POS] = KeyWrapper((unsigned char)'1');
		mappings[PlayerCommand::TEST_Z_NEG] = KeyWrapper((unsigned char)'2');
		mappings[PlayerCommand::TEST_NEW_BLOCK] = KeyWrapper((unsigned char)'3');
		mappings[PlayerCommand::TEST_COMMIT_BLOCK] = KeyWrapper((unsigned char)'4');
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

		mappings[PlayerCommand::TEST_Z_POS] = KeyWrapper((unsigned char)'7');
		mappings[PlayerCommand::TEST_Z_NEG] = KeyWrapper((unsigned char)'8');
		mappings[PlayerCommand::TEST_NEW_BLOCK] = KeyWrapper((unsigned char)'9');
		mappings[PlayerCommand::TEST_COMMIT_BLOCK] = KeyWrapper((unsigned char)'10');
		break;
	default:
		break;
	}
}

KeyWrapper KeyMapping::getActionKeyMapping(PlayerCommand::Action action)
{
	return mappings[action];
}

