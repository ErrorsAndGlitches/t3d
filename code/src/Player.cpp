#include <iostream>
#include "Player.h"

void Player::setArena(Arena &arena)
{
	this->arena = arena;
}


void Player::performAction(PlayerCommand::Action action)
{
	std::cout << action << std::endl;
	Player* ptr = this;
	arena.submitCommand(&ptr, PlayerCommand(action)); 
}