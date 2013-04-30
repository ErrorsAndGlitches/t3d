#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Arena.h"

class Player
{
public:
	Player(void);
	~Player(void){}
	

	/**
	* @brief Enum of player actions. 
	*/
	enum Action
	{
		ROTATE_X = 0,
		ROTATE_Y,
		ROTATE_Z,
		MOVE_X_POS,
		MOVE_X_NEG,
		MOVE_Y_POS,
		MOVE_Y_NEG,
		DROP_BLOCK,
		ACTION_COUNT			//Enum hack to give us access to enum cardinality. Must be last and no gaps allowed.
	};

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
	void performAction(Action action);

private:
	Arena arena;
};

#endif