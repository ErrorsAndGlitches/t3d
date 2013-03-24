#ifndef DRAWABLE_H
#define DRAWABLE_H
/**
 * @file
 * @brief Contains the abstract class Drawable
 * @author Benjamyn
 *
 * If the subclass does not override the draw method that takes a texture
 * handle as a parameter, then the no argument draw method is used.
 */

#include "GL/gl.h"

/**
 * @brief An interface for objects that can be drawn
 */
class Drawable {
	public:
		/**
		 * @brief Three element float array containing the values to draw in the
		 * color white
		 */
		static const float WHITE[];

		/**
		 * @brief Three element float array containing the values to draw in the
		 * color black
		 */
		static const float BLACK[];

		/**
		 * @brief Three element float array containing the values to draw in the
		 * default color, which is set to black
		 */
		static const float *const DEFAULT_COLOR;

		/**
		 * @brief Default draw method
		 */
		virtual void draw() const = 0;

		/**
		 * @brief Draw the object given the array of color
		 *
		 * @param color A three element color array
		 *
		 * If this draw method is not overriden, then the default argumentless draw
		 * method is used
		 */
		virtual void draw(const float *const color) const;

		/**
		 * @brief Draw the object given the texture handle
		 *
		 * @param texId An OpenGL texture handle
		 *
		 * If this draw method is not overriden, then the default argumentless draw
		 * method is used
		 */
		virtual void draw(const GLuint texId) const;
};

#endif
