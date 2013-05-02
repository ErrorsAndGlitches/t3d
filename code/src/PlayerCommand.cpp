#include <iostream>
#include "PlayerCommand.h"

PlayerCommand::PlayerCommand(Action action)
{
	this->action = action;
}

void PlayerCommand::execute(Subarena<> subarena)
{

	static int i = 0;
	switch (action)
	{
	case PlayerCommand::ROTATE_X:
		std::cout << i++ << ": Map 0" << std::endl;
		break;
	case PlayerCommand::ROTATE_Y:
		std::cout << i++ << ": Map 1" << std::endl;
		break;
	case PlayerCommand::ROTATE_Z:
		std::cout << i++ << ": Map 2" << std::endl;
		break;
	case PlayerCommand::MOVE_X_POS:
		std::cout << i++ << ": Map 3" << std::endl;
		break;
	case PlayerCommand::MOVE_X_NEG:
		std::cout << i++ << ": Map 4" << std::endl;
		break;
	case PlayerCommand::MOVE_Y_POS:
		std::cout << i++ << ": Map 5" << std::endl;
		break;
	case PlayerCommand::MOVE_Y_NEG:
		std::cout << i++ << ": Map 6" << std::endl;
		break;
	case PlayerCommand::DROP_BLOCK:
		std::cout << i++ << ": Map 7" << std::endl;
		break;
	default:
		break;
	}
}
	/*
	switch
	if ('a' == key)
		
	if ('d' == key)
		subarena->rotateSuperBlock(SimpleRotation::RotationType::YCW);
	if ('w' == key)
		subarena->rotateSuperBlock(SimpleRotation::RotationType::ZCW);
	if ('s' == key)
		subarena->moveSuperBlockRelative(Vector(0, 0, -1));
	if (' ' == key)
		subarena->newSuperBlock();

	if (GLUT_KEY_UP == key)
		subarena->moveSuperBlockRelative(Vector(0, 1, 0));
	if (GLUT_KEY_DOWN == key)
		subarena->moveSuperBlockRelative(Vector(0, -1, 0));
	if (GLUT_KEY_LEFT == key)
		subarena->moveSuperBlockRelative(Vector(-1, 0, 0));
	if (GLUT_KEY_RIGHT == key)
		subarena->moveSuperBlockRelative(Vector(1, 0, 0));
		
}*/