#ifndef ARENA_H
#define ARENA_H

#include "Subarena.h"
#include "Player.h"

class Arena
{
public:

	enum SubArena{
		TOP_ARENA,
		BOTTOM_ARENA
	};

	Arena(void);
	~Arena(void);

	/**
	* @brief Assigns the specified player to either the top or bottom subarena
	* @param &player a reference to the player beging assigned a sub arena
	* @param subarena The subarena being assigned to the specified player.
	*/
	void assignToArena(Player &player, SubArena subarena);
private:

	
	//subarenas and the players assigned to it
	Subarena<> subArenas[2]; 
	Player players[2];


};

#endif