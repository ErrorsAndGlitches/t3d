#ifndef PLAYER_H
#define PLAYER_H

#include "Arena.h"

class Player
{
public:

	/**
	* @brief Default Player constructor. Players are assigned 
	*		a unique ID upon creation.
	*/
	Player(void){playerID = playerIDGenerator++;}
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

	/**
	* @brief Gets the player's ID.
	*
	* @return The player ID
	*/
	int getID();

private:

	//The arena that this player submits commands to
	Arena arena;

	//We generate a unique ID for each player
	static int playerIDGenerator;
	int playerID;

};

#endif