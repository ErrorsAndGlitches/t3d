#include <iostream>
#include "Arena.h"
#include "Player.h"


Arena::Arena(void)
{
	subArenas[TOP_ARENA] = Subarena<>(); 
	subArenas[BOTTOM_ARENA] = Subarena<>(); 
}


void Arena::assignToArena(Player **player, SubArena subarena)
{
	(*player)->setArena(*this);
	players[subarena] = *player;
}

void Arena::submitCommand(Player **player, PlayerCommand &command)
{
	//Identify the sub arena to execute the command on, and execute it
	for (int subarena = 0; subarena < ARENA_COUNT; subarena++) {
		if (players[subarena] == *player) {
			command.execute(subArenas[subarena]);
		}
	}

}


void Arena::draw()
{
	for (int subarena = 0; subarena < 1; subarena++) {
		subArenas[subarena].Drawable::draw();
	}
}