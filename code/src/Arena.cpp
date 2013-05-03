#include <iostream>
#include "Arena.h"
#include "Player.h"


Arena::Arena(void)
{
	subArenas[TOP_ARENA] = Subarena<>(); 
	subArenas[BOTTOM_ARENA] = Subarena<>(); 
}


void Arena::assignToArena(Player *player, SubArena subarena)
{
	playerArenaMap.insert ( std::pair<SubArena,int>(subarena, player->getID()));
	player->setArena(this);
}

void Arena::submitCommand(Player *player, PlayerCommand command)
{
	std::map<SubArena, int>::iterator it;
	for (it = playerArenaMap.begin(); it != playerArenaMap.end(); it++) {
		if ((*it).second == player->getID()) {
		   SubArena subarena = (*it).first;
		   command.execute(&subArenas[subarena]);
	   }
	}
}


void Arena::draw()
{
	for (int subarena = 0; subarena < ARENA_COUNT; subarena++) {
		subArenas[subarena].Drawable::draw();
	}
}