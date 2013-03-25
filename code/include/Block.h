#ifndef BLOCK_H
#define BLOCK_H
/**
 * @file
 * @brief Contains the Block class declaration.
 * @author Benjamyn
 */

#include "GameObject.h"

/**
 * @brief A Block is a simple three dimensional block that is drawn such that
 * it is found entirely in the positive quandrant
 */
class Block: public GameObject {
	private:
		/**
		 * @brief Draw a colored block
		 *
		 * The color to use must already be set up and is used for all six faces
		 */
		void drawColoredBlock() const;

		/**
		 * @brief Draw a textured block
		 *
		 * The texture to use must already be set up and is used for all six faces
		 */
		void drawTexturedBlock() const;

	public:
		/**
		 * @brief Default constructor, sets the position to the origin
		 */
		Block(): GameObject() {}

		/**
		 * @brief Draws the block with the given color
		 *
		 * @param color A three element color array
		 */
		virtual void draw(const float *const color) const;

		/**
		 * @brief Draws the block with the given texture
		 *
		 * @param texId An OpenGL texture handle
		 */
		virtual void draw(const GLuint texId) const;
};

#endif
