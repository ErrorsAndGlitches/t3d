#ifndef ARENA_H
#define ARENA_H

#include "Subarena.h"
#include "PlayerCommand.h"
#include "Platform.h"
#include <map>
#include <functional>

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
	 * @brief Get the SuperBlock type in the local player's subarena
	 *
	 * @return The SuperBlock type
	 */
	SuperBlock::SuperBlockType getSuperBlockType() const;
	
	/**
	* @brief Draws the arena and subareans with the given color
	*
	* @param color A three element color array
	*
	* All the Blocks comprising the layer are colored the parameter
	* color
	*/
	virtual void draw(const float *const color) const;

	/**
	* @brief Draws the arena and subareans with the given texture
	*
	* @param texId An OpenGL texture handle
	*
	* All the Blocks comprising the layer are textured the parameter
	* texture
	*/
	virtual void draw(const GLuint texId) const;

	/**
	* @brief Draws the subarean with the default drawing method
	*
	*/
	virtual void draw() const;

	/**
	* @brief Reset the arena.
	*
	*/
	void reset();

	/**
	 * @brief Set the command to call when a command is submitted to the arena
	 *
	 * @param submitNetworkCommandFunc Command function
	 */
	void setNetworkSubmitFunction(std::function<void (PlayerCommand)> submitNetworkCommandFunc);

	/**
	 * @brief Submit a command received from a network player
	 *
	 * @param command The command received from the network player
	 */
	void submitNetworkPlayerCommand(PlayerCommand command);

	/**
	 * @brief Set whether the network player's SuperBlock should be drawn
	 *
	 * @param isDrawn If true, the other player's SuperBlock is drawn
	 */
	void drawNetworkPlayerSuperBlock(bool isDrawn);

	/**
	 * @brief Set the SuperBlock type of the network player's SuperBlock
	 *
	 * @param sbType SuperBlock type to set to
	 */
	void setNetworkPlayerSuperBlockType(SuperBlock::SuperBlockType sbType);

private:

	int center;

	//subarenas and the players assigned to it
	Subarena<> subArenas[ARENA_COUNT];
	std::map<SubArena, Player*> playerArenaMap;
	// function used to submit PlayerCommands to the network
	std::function<void (PlayerCommand)> submitNetworkCommandFunc;

	/**
	* @brief Clears all the full layers of a particular sub arena, and updates the layers.
	* @param subarena The subarena that is to have its layers cleared.
	* @return the number of layers cleared
	*/
	int clearFullLayers(SubArena subarena);

	/**
	* @brief Draws a plateform in the arena between the two subarenas
	*/
	void drawPlateform() const;


	/**
	* @brief Ends the game due to a player hitting the top of the arena.
	* @param playerID The id of the player that lost
	*/
	void endByPlayerFault(int playerID);

	/**
	* @brief Checks to see if either of the players have lost
	*/
	void checkEndCondition();

	/**
	* @brief Updates the layers of the subarena after a block drop. This involves potential platform moving, 
	* layer clearing
	* @param subarena The arena being that is having it's layers checked
	*/
	void updateLayers(SubArena subarena);
};

#endif
