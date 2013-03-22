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
	protected:
		/**
		 * @brief Draw a colored block
		 *
		 * The color to use must already be set up and is used for all six faces
		 */
		virtual void drawColoredGameObject();

		/**
		 * @brief Draw a textured block
		 *
		 * The texture to use must already be set up and is used for all six faces
		 */
		virtual void drawTexturedGameObject();

	public:
		/**
		 * @brief Default constructor, sets the position to the origin
		 */
		Block(): GameObject() {}
};

#endif
