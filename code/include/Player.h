#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#ifdef _WIN32
	#include <windows.h>
#endif
#include <gl/glut.h>

#include "KeyWrapper.h"


/**
 * @file
 * @brief Contains the Player class declaration.
 * @author Zach
 */


/**
 * @brief A Player controls blocks associatd with a particular sub arena. Keyboard controls
 *			are also done through the player class.
 */
class Player
{
public:

	/**
	* @brief Initializes the player.
	*/
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
	* @brief Enum of default keyboard mappings. 
	*/
	enum DefaultMapping
	{
		SINGLE_PLAYER,
		MULTI_PLAYER_A,
		MULTI_PLAYER_B
	};

	/**
	* @brief Set the keyboard mapping
	*
	* @param action The player action to be mapped
	* @param keyMapping The keyboard value being mapped to the action
	*/
	void setActionKeyMapping(Action action, int keyMapping);

	/**
	* @brief Set the keyboard mapping
	*
	* @param action The player action to be mapped
	* @param keyMapping The keyboard value being mapped to the action
	*/
	void setActionKeyMapping(Action action, unsigned char keyMapping);



	/**
	* @brief Set the default keyboard mapping
	*
	* @param DefaultMapping The default mapping.
	*/
	void setDefaultMapping(DefaultMapping mapping);

	/**
	* @brief Perform the action (if any) associated with the given keyboard input.
	*
	* @param key The input key
	*/
	void processKeyboardInput(int key);

	/**
	* @brief Perform the action (if any) associated with the given keyboard input.
	*
	* @param key The input key
	*/
	void processKeyboardInput(unsigned char key);

private:

	//List of key/action mappings
	KeyWrapper mappings[ACTION_COUNT];


	/**
	* @brief Perform the specified action.
	*
	* @param action The action to perform
	*/
	void performAction(Action action);
};

#endif