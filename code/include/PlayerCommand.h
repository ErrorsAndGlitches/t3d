#ifndef PLAYER_COMMAND_H
#define PLAYER_COMMAND_H

#include "Subarena.h"
/**
 * @file
 * @brief Contains the Player Command class declaration.
 * @author Zach
 */

/**
 * @brief A player command encapsulates a command that a player can send perform
 */
class PlayerCommand
{
public:

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
		TEST_Z_POS, 
		TEST_Z_NEG, 
		TEST_NEW_BLOCK, 
		TEST_COMMIT_BLOCK,
		ACTION_COUNT			//Enum hack to give us access to enum cardinality. Must be last and no gaps allowed.
	};

	/**
	* @brief Default construtor
	*/
	PlayerCommand(){}

	/**
	* @brief Construct a player command with the specified action
	* @param action the action being encapsulated by this object
	*/
	PlayerCommand(Action action);
	~PlayerCommand(void){}

	

	/**
	* @brief Execute this action on the specified subarena
	* @param SubArena a pointer to the subarena this command will be executed on
	*/
	void execute(Subarena<> *subarena);

	
	/**
	* @brief Get the action of this player command
	* @return The action of this player command.
	*/
	Action getAction();

private:

	//The action of this command
	Action action;

	/**
	* @brief Execute a move command on the sub arena
	* @param v The movement vector
	* @param *subarena The subarena to execute the move on.
	*/
	void executeMove(Vector v, Subarena<> *subarena);

	/**
	* @brief Execute a rotation command on the sub arena
	* @param rot The rotation type
	* @param *subarena The subarena to execute the rotation on.
	*/
	void executeRotation(SimpleRotation::RotationType rot, Subarena<> *subarena);

	/**
	* @brief Execute a drop block action on the specified subarena, commit the block.
	* @param SubArena a pointer to the subarena this command will be executed on
	*/
	void dropAndCommitBlock(Subarena<> *subarena);

};

#endif
