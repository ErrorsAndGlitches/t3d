#include <iostream>
#include "Arena.h"
#include "Player.h"


Arena::Arena(void): GameObject()
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


void Arena::draw(const float *const color) const 
{

	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		for (int subarena = 0; subarena < ARENA_COUNT; subarena++) {
			subArenas[subarena].draw(color);
		}
	glPopMatrix();
}

void Arena::draw(const GLuint texId) const 
{

	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		for (int subarena = 0; subarena < ARENA_COUNT; subarena++) {
			subArenas[subarena].draw(texId);
		}
	glPopMatrix();
}