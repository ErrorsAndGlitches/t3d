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
 * All game objects in the gaming window derive from this class.
 * The class provides some basic operations that all the tokens
 * of the game should support
 */
class GameObject: public Drawable {
	protected:
		Vector pos; // from origin

		/**
		 * @brief Draw a colored game object
		 *
		 * The color to use must already be set up
		 */
		virtual void drawColoredGameObject() const = 0;

		/**
		 * @brief Draw the game object given the texture handle
		 *
		 * The texture to use must already be bound
		 */
		virtual void drawTexturedGameObject() const = 0;

	public:
		/**
		 * @brief Default constructor, sets the position to the origin
		 */
		GameObject(): pos() {}

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

		/**
		 * @brief Draws the game object in the default color. See Drawable for the
		 * default color
		 */
		virtual void draw() const;

		/**
		 * @brief Draws the game object with the given colors
		 *
		 * @param color A three element color array
		 *
		 * This function wraps the drawGameObject(const float *const color) const
		 * function so that subclasses only need to worry about the actual drawing
		 * and not setting up the colors
		 */
		void draw(const float *const color) const;

		/**
		 * @brief Draws the game object with the given textures
		 *
		 * @param texId An OpenGL texture handle
		 *
		 * This function wraps the drawGameObject(const GLuint texId) const
		 * function so that subclasses only need to worry about the actual drawing
		 * and not setting up the textures 
		 */
		void draw(const GLuint texId) const;
};

#endif
