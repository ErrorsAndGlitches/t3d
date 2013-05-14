#ifndef PLAYER_H
#define PLAYER_H

#include "Arena.h"

/**
 * @file
 * @brief Contains the Player class declaration.
 * @author Zach
 */


/**
 * @brief Class representing a player in the game. Players 
 *		is the gatekeeper for all player commands and controls which subarena
 *      a player can interact with.
 */
class Player
{
public:

	/**
	* @brief Default Player constructor. Players subscribe to
	*		arena's and and send commands to that arena
	*/
	Player(void);
	~Player(void){}
	

	/**
	* @brief Sets the arena assoicated with this player.
	*
	* @param *arena The arena to assign to this player
	*/
	void setArena(Arena *arena);

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
	Arena *arena;

	//We generate a unique ID for each player
	static int playerIDGenerator;
	int playerID;
	
};

#endif