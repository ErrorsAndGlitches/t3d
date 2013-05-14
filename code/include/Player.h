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

	/**
	* @brief Gets the player's score.
	*
	* @return The players score
	*/
	int getScore() {return score;}

	/**
	* @brief Reset the player's score.
	*
	*/
	void resetScore() {score = 0;}

	/**
	* @brief Add the specified number of points to the player's score.
	*
	* @param The number of points to add
	*/
	void addToScore(int points) { score += points;}

private:

	//The arena that this player submits commands to
	Arena *arena;

	//We generate a unique ID for each player
	static int playerIDGenerator;
	int playerID;
	
	//Player score
	int score;

};

#endif