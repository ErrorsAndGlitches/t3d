#ifndef PLAYER_H
#define PLAYER_H

#include "Arena.h"

class Player
{
public:
	Player(void){}
	~Player(void){}
	

	/**
	* @brief Sets the arena assoicated with this player.
	*
	* @param &arena The arena to assign to this player
	*/
	void setArena(Arena &arena);

	/**
	* @brief Perform the specified action.
	*
	* @param action The action to perform
	*/
	void performAction(PlayerCommand::Action action);

private:
	Arena arena;
};

#endif