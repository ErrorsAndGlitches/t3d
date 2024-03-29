#include <iostream>
#include "Player.h"

int Player::playerIDGenerator = 1;

Player::Player()
{
	playerID = playerIDGenerator++;
}

void Player::setArena(Arena *arena)
{
	this->arena = arena;
}

int Player::getID()
{
	return playerID;
}

void Player::performAction(PlayerCommand::Action action)
{
	arena->submitCommand(this, PlayerCommand(action)); 
}