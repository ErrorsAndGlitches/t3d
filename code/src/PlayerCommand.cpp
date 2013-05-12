#include <iostream>
#include "PlayerCommand.h"

PlayerCommand::PlayerCommand(Action action)
{
	this->action = action;
}

PlayerCommand::Action PlayerCommand::getAction()
{
	return action;
}

void PlayerCommand::execute(Subarena<> *subarena)
{

	static int i = 0;
	switch (action)
	{
	case PlayerCommand::ROTATE_X:
		executeRotation(SimpleRotation::RotationType::XCW, subarena);
		std::cout << i++ << ": ROTATE_X" << std::endl;
		break;
	case PlayerCommand::ROTATE_Y:
		executeRotation(SimpleRotation::RotationType::YCW, subarena);
		std::cout << i++ << ": ROTATE_Y" << std::endl;
		break;
	case PlayerCommand::ROTATE_Z:
		executeRotation(SimpleRotation::RotationType::ZCW, subarena);
		std::cout << i++ << ": ROTATE_Z" << std::endl;
		break;
	case PlayerCommand::MOVE_X_POS:
		executeMove(Vector(1, 0, 0), subarena);
		std::cout << i++ << ": MOVE_X_POS" << std::endl;
		break;
	case PlayerCommand::MOVE_X_NEG:
		executeMove(Vector(-1, 0, 0), subarena);	
		std::cout << i++ << ": MOVE_X_NEG" << std::endl;
		break;
	case PlayerCommand::MOVE_Y_POS:
		executeMove(Vector(0, 1, 0), subarena);
		std::cout << i++ << ": MOVE_Y_POS" << std::endl;
		break;
	case PlayerCommand::MOVE_Y_NEG:
		executeMove(Vector(0, -1, 0), subarena);
		std::cout << i++ << ": MOVE_Y_NEG" << std::endl;
		break;
	case PlayerCommand::DROP_BLOCK:
		dropAndCommitBlock(subarena);
		subarena->dropSuperBlock();
		std::cout << i++ << ": DROP_BLOCK" << std::endl;
		break;
	case PlayerCommand::TEST_Z_POS:
		executeMove(Vector(0, 0, 1), subarena);
		std::cout << i++ << ": TEST_Z_POS" << std::endl;
		break;
	case PlayerCommand::TEST_Z_NEG:
		executeMove(Vector(0, 0, -1), subarena);
		std::cout << i++ << ": TEST_Z_NEG" << std::endl;
		break;
	case PlayerCommand::TEST_NEW_BLOCK:
		subarena->newSuperBlock();
		std::cout << i++ << ": TEST_NEW_BLOCK" << std::endl;
		break;
	case PlayerCommand::TEST_COMMIT_BLOCK:
		subarena->insertSuperBlockIntoLayers();
		std::cout << i++ << ": TEST_COMMIT_BLOCK" << std::endl;
		break;
	default:
		break;
	}
}

void PlayerCommand::executeMove(Vector v, Subarena<> *subarena)
{
	if (subarena->canMoveSuperBlockRelative(v)) {
		subarena->moveSuperBlockRelative(v);
	}
}

void PlayerCommand::executeRotation(SimpleRotation::RotationType rot, Subarena<> *subarena)
{
	if (subarena->canRotateSuperBlock(rot)) {
		subarena->rotateSuperBlock(rot);
	}
}

void PlayerCommand::dropAndCommitBlock(Subarena<> *subarena)
{
	subarena->dropSuperBlock();
	subarena->insertSuperBlockIntoLayers();
}