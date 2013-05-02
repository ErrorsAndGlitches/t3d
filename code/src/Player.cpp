#include "Player.h"



void Player::setArena(Arena &arena)
{
	this->arena = arena;
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