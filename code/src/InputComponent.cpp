#include "InputComponent.h"


void InputComponent::bindPlayerToMapping(Player player, KeyMapping mapping)
{
	this->player = player;
	this->keyMapping = mapping;
}


void InputComponent::processKeyboardInput(unsigned char key)
{
	int action;
	for (action = 0; action < PlayerCommand::ACTION_COUNT; action++)
	{
		if (keyMapping.getActionKeyMapping(static_cast<PlayerCommand::Action>(action)).equals(key))
		{
			player.performAction( static_cast<PlayerCommand::Action>(action) );
		}
	}
	
}

void InputComponent::processKeyboardInput(int key)
{
	int action;
	for (action = 0; action < PlayerCommand::ACTION_COUNT; action++)
	{

		if (keyMapping.getActionKeyMapping(static_cast<PlayerCommand::Action>(action)).equals(key))
		{
			player.performAction( static_cast<PlayerCommand::Action>(action) );
		}
	}
	
}
