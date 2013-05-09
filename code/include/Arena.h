#ifndef ARENA_H
#define ARENA_H

#include "Subarena.h"
#include "PlayerCommand.h"
#include "Platform.h"
#include <map>

/**
 * @file
 * @brief Contains the Arena class declaration.
 * @author Zach
 */


//Forward declariation of player class
class Player;

/**
 * @brief An arena encapsulates all the actions of the game. It
 *		is the gatekeeper for all player commands and controls which subarena
 *      a player can interact with.
 */
class Arena: public GameObject
{
public:

	/**
	* @brief Enum of different sub arenas. 
	*/
	enum SubArena{
		TOP_ARENA,
		BOTTOM_ARENA, 
		ARENA_COUNT			//Hack to get enum size
	};

	/**
	* @brief Default Area Contructor.
	*/
	Arena(void);
	~Arena(void){}

	/**
	* @brief Assigns the specified player to either the top or bottom subarena
	* @param *player a pointer to the player beging assigned a sub arena
	* @param subarena The subarena being assigned to the specified player.
	*/
	void assignToArena(Player *player, SubArena subarena);

	/**
	* @brief Submit a command to the arena. The command will be executed on the subarena(s)
	*			assigned to the player.
	* @param *player a pointer to the player issueing the command
	* @param command The command to execute.
	*/
	void submitCommand(Player *player, PlayerCommand command);
	
	/**
	* @brief Draws the subarean's layer with the given color
	*
	* @param color A three element color array
	*
	* All the Blocks comprising the layer are colored the parameter
	* color
	*/
	virtual void draw(const float *const color) const;

	/**
	* @brief Draws the subarean's layer with the given texture
	*
	* @param texId An OpenGL texture handle
	*
	* All the Blocks comprising the layer are textured the parameter
	* texture
	*/
	virtual void draw(const GLuint texId) const;


private:

	//subarenas and the players assigned to it
	Subarena<> subArenas[ARENA_COUNT];
	std::map<SubArena, int> playerArenaMap;

	Platform platform;

	/**
	* @brief Draws a plateform in the arena between the two subarenas
	*/
	void drawPlateform() const;
};

#endif
