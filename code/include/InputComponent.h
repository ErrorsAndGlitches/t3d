#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <iostream>
#ifdef _WIN32
	#include <windows.h>
#endif
#include <gl/glut.h>


#include "Player.h"
#include "PlayerCommand.h"
#include "KeyMapping.h"


/**
 * @file
 * @brief Contains the input component class declaration.
 * @author Zach
 */


/**
 * @brief The input component serves to map input commands to player actions. It works
 *			by binding a player to a keyboard mapping, then intercepting keyboard inputs
 *			and signaling a player to perform a given action based on the input.
 */
class InputComponent
{
public:

	/**
	* @brief Initializes the Input Component.
	*/
	InputComponent(void){}
	~InputComponent(void){}

	/**
	* @brief Binds a player to the designated mapping within this input controller
	*
	* @param *player The player to be bound to the given mapping within this controller
	* @param mapping The mapping to be bound the given player within this controller
	*/
	void bindPlayerToMapping(Player *player, KeyMapping mapping);

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
	
	//The player this input component is attached to
	Player *player;

	//The keyboard mappings for this input controller
	KeyMapping keyMapping;

};

#endif