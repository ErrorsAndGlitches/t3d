#ifndef WORLD_H
#define WORLD_H
/**
 * @file
 * @brief Contains the World class declaration.
 * @author Zach
 */

#include "Platform.h"
#include "Arena.h"
#include "NetworkInterface.h"
#include "Jukebox.h"

/**
 * @brief The world encompases the entire scene of the game.
 *			It controls what the player is looking at.
 */
class World
{
public:
	typedef enum {
		HOST,
		CLIENT,
		NUMBER_NETWORK_PLAYER_TYPES
	} NetworkPlayerType;

	/**
	* @brief Default constructor
	*
	*/
	World(NetworkPlayerType npType);
	~World(void) {}

	/**
	* @brief Sets the world's focus to the given arena
	*
	* @param *arena The arena the world is focused 
	*/
	void setArena(Arena* arena);
	
	/**
	* @brief Initalized the default values of the world
	*
	*/
	void init();

	/**
	 * @brief Start a network game by initiating communication with another
	 * network player
	 */
	void startNetworkGame();

	/**
	* @brief Resets the state of the game
	*
	*/
	void reset();

	/**
	* @brief Draws everything in the game
	*/
	void draw();

	/**
	* @brief Set the aspect ratio of the camera
	* @param ratio The aspect ratio
	*/
	void setAspectRatio(float ratio);

	/**
	* @brief Mouse move callback. Mouse movement controls the world view perspective
	* @param xx Horizontal location of the mouse
	* @param yy Vertical location of the mouse
	*/
	void mouseMove(int xx, int yy); // mouse dragged

	/**
	* @brief Mouse clicked callback. Enables world view perspective dragging
	* @param button The mouse button clicked
	* @param state Was it a press/release
	* @param xx Horizontal location of the mouse click
	* @param yy Vertical location of the mouse click
	*/
	void mouseButton(int button, int state, int xx, int yy); // mouse button

	/**
	* @brief Positions the camera.
	*/
	void setUpCamera();

	/**
	 * @brief Updates the state of the network player if we receive input from them
	 */
	void updateNetworkPlayer();

	/**
	 * @brief toggle the music
	 */
	void toggleMusic();

	/**
	 * @brief Set the state of the world
	 *
	 * @param newState The new state of the world
	 */
	void setWorldState(GameState newState);

private: 
	/**
	 * @brief Draw the world for a running game
	 */
	void drawRunningState();

	/**
	 * @brief Draw the background
	 */
	void drawBackground();

	/**
	 * @brief Draw a screen indicating the player lost
	 */
	void drawLostState();

	/**
	 * @brief Draw a screen indicating the player won
	 */
	void drawWonState();

	/**
	 * @brief Draw text on the screen
	 */
	void drawScreenText();

private:
	GameState worldState;
	char *screenText;

	Arena* arena;		//The arena this world is fouced on
	int length;			//The dimension of the arean
	int height;			//Theheight of the arena

	float aspectRatio;	// aspect ratio of graphics window
	
	bool isDragging;	// true when mouse is dragging
	int xDragStart;		// records the x-coordinate when dragging starts
	int yDragStart;		// records the x-coordinate when dragging starts
	float xRotation;	//How much to rotate world about x axis
	float zRotation;	//How much to rotate world about z axis

	//How much the user is currently rotating the world beyond x/zRotation
	float xRotationDelta;	
	float zRotationDelta;
	
	int orientaion;	//Whether the world is upsidedown;

	// interface to perform networking operations
	NetworkInterface netInt;
	NetworkPlayerType npType;

	Jukebox *jukebox;
};

#endif
