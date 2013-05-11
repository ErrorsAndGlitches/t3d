#include <iostream>
#include "PlayerCommand.h"

PlayerCommand::PlayerCommand(Action action)
{
	this->action = action;
}

void PlayerCommand::execute(Subarena<> *subarena)
{

	static int i = 0;
	switch (action)
	{
	case PlayerCommand::ROTATE_X:
		executeRotation(SimpleRotation::RotationType::XCW, subarena);
		std::cout << i++ << ": Map 0" << std::endl;
		break;
	case PlayerCommand::ROTATE_Y:
		executeRotation(SimpleRotation::RotationType::YCW, subarena);
		std::cout << i++ << ": Map 1" << std::endl;
		break;
	case PlayerCommand::ROTATE_Z:
		executeRotation(SimpleRotation::RotationType::ZCW, subarena);
		std::cout << i++ << ": Map 2" << std::endl;
		break;
	case PlayerCommand::MOVE_X_POS:
		executeMove(Vector(1, 0, 0), subarena);
		std::cout << i++ << ": Map 3" << std::endl;
		break;
	case PlayerCommand::MOVE_X_NEG:
		executeMove(Vector(-1, 0, 0), subarena);	
		std::cout << i++ << ": Map 4" << std::endl;
		break;
	case PlayerCommand::MOVE_Y_POS:
		executeMove(Vector(0, 1, 0), subarena);
		std::cout << i++ << ": Map 5" << std::endl;
		break;
	case PlayerCommand::MOVE_Y_NEG:
		executeMove(Vector(0, -1, 0), subarena);;
		std::cout << i++ << ": Map 6" << std::endl;
		break;
	case PlayerCommand::DROP_BLOCK:
		//TODO: switch back to drop block
		subarena->dropSuperBlock();
		std::cout << i++ << ": Map 7" << std::endl;
		break;
	default:
		break;
	}
}

void PlayerCommand::executeMove(Vector v, Subarena<> *subarena)
{
	if (subarena->canMoveSuperBlockRelative(v)) {
		std::cout << "true" << std::endl;
		subarena->moveSuperBlockRelative(v);
	}
}

void PlayerCommand::executeRotation(SimpleRotation::RotationType rot, Subarena<> *subarena)
{
	if (subarena->canRotateSuperBlock(rot)) {
		std::cout << "true" << std::endl;
		subarena->rotateSuperBlock(rot);
	}
}