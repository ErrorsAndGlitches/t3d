#ifndef WORLD_H
#define WORLD_H
/**
 * @file
 * @brief Contains the World class declaration.
 * @author Zach
 */

#include "Platform.h"

/**
 * @brief The world encompases the entire scene of the game
			any global modifactions to the game are processed
			through and eventually reflected in the world class.
 */
class World
{
public:

	/**
	* @brief Constructs the world with the given dimension
	*
	* @param dimension The dimension of the world affect the size of the arena (in blocks)
					and camera placement. 
	*/
	World(int dimension = 4);
	~World(void) {}

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

private:
	Platform plateform;
	int dimension;		//The dimension of the arean

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


};

#endif