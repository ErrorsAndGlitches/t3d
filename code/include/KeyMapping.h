#ifndef KEYMAPPING_H
#define KEYMAPPING_H

#include "KeyWrapper.h"
#include "Player.h"
/**
 * @file
 * @brief Contains the Key Mapping class declaration.
 * @author Zach
 */


/**
 * @brief A KeyMapping defines a default set of key-action mappings for a player
 */
class KeyMapping
{
public:
	KeyMapping(){}
	~KeyMapping(void){}

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
	* @brief Set the default keyboard mapping
	*
	* @param DefaultMapping The default mapping.
	*/
	void setDefaultMapping(DefaultMapping mapping);

	/**
	* @brief Set the keyboard mapping
	*
	* @param action The player action to be mapped
	* @param keyMapping The keyboard value being mapped to the action
	*/
	void setActionKeyMapping(Player::Action action, int keyMapping);

	
	/**
	* @brief Set the keyboard mapping
	*
	* @param action The player action to be mapped
	* @param keyMapping The keyboard value being mapped to the action
	*/
	void setActionKeyMapping(Player::Action action, unsigned char keyMapping);

	/**
	* @brief Get the key tied to this action
	* @return the key tied to this action
	*
	*/
	KeyWrapper getActionKeyMapping(Player::Action action);

private:

	//List of key/action mappings
	KeyWrapper mappings[Player::ACTION_COUNT];

};


#endif