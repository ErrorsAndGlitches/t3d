#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
/**
 * @file
 * @brief Contains the GameObject abstract class declaration.
 * @author Benjamyn
 */

#include "Vector.h"
#include "Drawable.h"

/**
 * @brief All objects in the main screen are considered game objects
 *
 * All game objects in the gaming derive from this class.  The class provides
 * some basic operations that all the tokens of the game should support.
 */
class GameObject: public Drawable {
	protected:
		Vector pos; // from origin

	public:
		/**
		 * @brief Default constructor, sets the position to the origin
		 */
		GameObject(): Drawable(), pos() {}

		/**
		 * @brief Constructor that takes a position of the game object as a
		 * parameter
		 */
		GameObject(const Vector &v): Drawable(), pos(v) {}

		/**
		 * @brief Update the position by providing a relative value
		 * to the current position
		 *
		 * @param xRel Relative change in x postion
		 * @param yRel Relative change in y postion
		 * @param zRel Relative change in z postion
		 */
		void updateRelaPos(float xRel, float yRel, float zRel);

		/**
		 * @brief Update the position by providing a relative value
		 * to the current position
		 *
		 * @param p Relative change to current position
		 */
		void updateRelaPos(const Vector& p);

		/**
		 * @brief Set the game object's position
		 *
		 * @param v The new position
		 */
		void setPos(const Vector& v);

		/**
		 * @brief Return the current position of the game object
		 *
		 * @return The current position of the game object
		 */
		Vector getPos() const;
};

#endif
