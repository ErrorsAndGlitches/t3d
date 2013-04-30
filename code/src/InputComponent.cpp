#include "InputComponent.h"


void InputComponent::bindPlayerToMapping(Player player, KeyMapping mapping)
{
	this->player = player;
	this->keyMapping = mapping;
}


void InputComponent::processKeyboardInput(unsigned char key)
{
	int action;
	for (action = 0; action < Player::ACTION_COUNT; action++)
	{
		if (keyMapping.getActionKeyMapping(static_cast<Player::Action>(action)).equals(key))
		{
			player.performAction( static_cast<Player::Action>(action) );
		}
	}
	
}

void InputComponent::processKeyboardInput(int key)
{
	int action;
	for (action = 0; action < Player::ACTION_COUNT; action++)
	{

		if (keyMapping.getActionKeyMapping(static_cast<Player::Action>(action)).equals(key))
		{
			player.performAction( static_cast<Player::Action>(action) );
		}
	}
	
}
