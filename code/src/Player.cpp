#include "Player.h"


Player::Player(void)
{

}


void Player::setActionKeyMapping(Action action, int keyMapping)
{
	mappings[action] = KeyWrapper(keyMapping);
}

void Player::setActionKeyMapping(Action action, unsigned char keyMapping)
{
	mappings[action] = KeyWrapper(keyMapping);
}


void Player::setDefaultMapping(DefaultMapping mapping)
{
	switch (mapping)
	{
	case Player::SINGLE_PLAYER:
		mappings[ROTATE_X] = KeyWrapper((unsigned char)'z'); 
		mappings[ROTATE_Y] = KeyWrapper((unsigned char)'x');
		mappings[ROTATE_Z] = KeyWrapper((unsigned char) 'c');
		mappings[MOVE_X_POS] = KeyWrapper((unsigned char) 'd'); 
		mappings[MOVE_X_NEG] = KeyWrapper((unsigned char) 'a'); 
		mappings[MOVE_Y_POS] = KeyWrapper((unsigned char) 'w'); 
		mappings[MOVE_Y_NEG] = KeyWrapper((unsigned char) 's');
		mappings[DROP_BLOCK] = KeyWrapper((unsigned char)' '); 
		break;
	case Player::MULTI_PLAYER_A:
		mappings[ROTATE_X] = KeyWrapper((unsigned char)'z'); 
		mappings[ROTATE_Y] = KeyWrapper((unsigned char)'x');
		mappings[ROTATE_Z] = KeyWrapper((unsigned char) 'c');
		mappings[MOVE_X_POS] = KeyWrapper((unsigned char) 'd'); 
		mappings[MOVE_X_NEG] = KeyWrapper((unsigned char) 'a'); 
		mappings[MOVE_Y_POS] = KeyWrapper((unsigned char) 'w'); 
		mappings[MOVE_Y_NEG] = KeyWrapper((unsigned char) 's');
		mappings[DROP_BLOCK] = KeyWrapper((unsigned char)' '); 
		break;
	case Player::MULTI_PLAYER_B:
		mappings[ROTATE_X] = KeyWrapper((unsigned char)','); 
		mappings[ROTATE_Y] = KeyWrapper((unsigned char)'.');
		mappings[ROTATE_Z] = KeyWrapper((unsigned char) '/');
		mappings[MOVE_X_POS] = KeyWrapper((unsigned char) '\''); 
		mappings[MOVE_X_NEG] = KeyWrapper((unsigned char) 'l'); 
		mappings[MOVE_Y_POS] = KeyWrapper((unsigned char) 'p'); 
		mappings[MOVE_Y_NEG] = KeyWrapper((unsigned char) ';');
		mappings[DROP_BLOCK] = KeyWrapper((unsigned char)'\r'); 
		break;
	default:
		break;
	}
}

void Player::processKeyboardInput(unsigned char key)
{
	int action;
	for (action = 0; action < ACTION_COUNT; action++)
	{
		if (mappings[action].equals(key))
		{
			performAction( static_cast<Action>(action) );
		}
	}
	
}

void Player::processKeyboardInput(int key)
{
	int action;
	for (action = 0; action < ACTION_COUNT; action++)
	{

		if (mappings[action].equals(key))
		{
			performAction( static_cast<Action>(action) );
		}
	}
	
}

void Player::performAction(Action action)
{
	static int i = 0;
	switch (action)
	{
	case Player::ROTATE_X:
		std::cout << i++ << ": Map 0" << std::endl;
		break;
	case Player::ROTATE_Y:
		std::cout << i++ << ": Map 1" << std::endl;
		break;
	case Player::ROTATE_Z:
		std::cout << i++ << ": Map 2" << std::endl;
		break;
	case Player::MOVE_X_POS:
		std::cout << i++ << ": Map 3" << std::endl;
		break;
	case Player::MOVE_X_NEG:
		std::cout << i++ << ": Map 4" << std::endl;
		break;
	case Player::MOVE_Y_POS:
		std::cout << i++ << ": Map 5" << std::endl;
		break;
	case Player::MOVE_Y_NEG:
		std::cout << i++ << ": Map 6" << std::endl;
		break;
	case Player::DROP_BLOCK:
		std::cout << i++ << ": Map 7" << std::endl;
		break;
	default:
		break;
	}
}