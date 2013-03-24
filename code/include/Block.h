#ifndef BLOCK_H
#define BLOCK_H
/**
 * @file
 * @brief Contains the Block class declaration.
 * @author Benjamyn
 */

#include "GameObject.h"
#include "SuperBlock.h"

class SuperBlock;

/**
 * @brief A Block is a simple three dimensional block that is drawn such that
 * it is found entirely in the positive quandrant
 */
class Block: public GameObject {
	friend class SuperBlock;

	protected:
		/**
		 * @brief Draw a colored block
		 *
		 * The color to use must already be set up and is used for all six faces
		 */
		virtual void drawColoredGameObject() const;

		/**
		 * @brief Draw a textured block
		 *
		 * The texture to use must already be set up and is used for all six faces
		 */
		virtual void drawTexturedGameObject() const;

	public:
		/**
		 * @brief Default constructor, sets the position to the origin
		 */
		Block(): GameObject() {}
};

#endif
