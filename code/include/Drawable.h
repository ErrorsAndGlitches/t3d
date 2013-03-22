#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "GL/gl.h"

/**
 * @brief Contains the abstract class Drawable
 * @author Benjamyn
 *
 * If the subclass does not override the draw method that takes a texture
 * handle as a parameter, then the no argument draw method is used.
 */

/**
 * @brief An interface for objects that can be drawn
 */
class Drawable {
	public:
		/**
		 * @brief Default draw method
		 */
		virtual void draw() const = 0;

		/**
		 * @brief Draw the object given the array of texture handles
		 *
		 * @param texId An array of OpenGL texture handle
		 *
		 * If this draw method is not override, then the default argumentless draw
		 * method is used
		 */
		virtual void draw(GLuint *texId) const;
};

#endif
