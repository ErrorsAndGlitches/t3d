#ifndef SUPER_BLOCK_H
#define SUPER_BLOCK_H
/**
 * @file
 * @brief Contains the SuperBlock class declaration.
 * @author Benjamyn
 */

#include "Vector.h"
#include "Block.h"
#include <vector>
#include <functional>

class Block;

/**
 * @brief A SuperBlock is composed of a set of Block objects. 
 *
 * A super block supports rotation the block about rotation point, which is
 * usually close to its center of mass, however, this is not always possible
 * since after rotations are applied, the block must still have its edges at
 * unit distances. All rotations are 90 degree rotations about the axis in the
 * function name e.g.  SuperBlock::rotateX() rotates the object 90 degrees
 * about the x-axis
 */
class SuperBlock: public GameObject {
	private:
		enum Rotation { ROT_X, ROT_Y, ROT_Z };

		static Block *block; // shared block for drawing
		// location of blocks where the figure is drawn entirely in the positive
		// quadrant
		std::vector<Vector> blockLocs;
		Vector rotPtToOrigin; // translation of block so rotation point is at the origin

		std::vector<Rotation> rotations; // rotations that have been applied
		// TODO: more efficient way to remember rotations instead of building a
		// stack
		
		/**
		 * @brief Initializes the super block to be a line super block
		 */
		void createLineSuperBlock();

		/**
		 * @brief Initializes the super block to be a cube super block
		 */
		void createCubeSuperBlock();

		/**
		 * @brief Initializes the super block to be a ell super block
		 */
		void createEllSuperBlock();

		/**
		 * @brief Initializes the super block to be a ess super block
		 */
		void createEssSuperBlock();

		/**
		 * @brief Initializes the super block to be a pyramid super block
		 */
		void createPyramidSuperBlock();

		/**
		 * @brief Wraps the blockDrawFunc in the translation and rotation
		 * operations so that the same operations can be used for the colored and
		 * textured block drawing
		 *
		 * @param blockDrawFunc Function that should be called when a block should
		 * be drawn
		 */
		void drawBlockList(std::function<void ()> blockDrawFunc) const;

	protected:
		/**
		 * @brief Draw a colored super block
		 *
		 * All the Block objects of the SuperBlock are colored the same
		 */
		virtual void drawColoredGameObject() const;

		/**
		 * @brief Draw a textured super block
		 *
		 * All the Block objects of the SuperBlock are textured the same
		 */
		virtual void drawTexturedGameObject() const;

	public:
		/**
		 * @brief Different types of super blocks
		 */
		enum SuperBlockType { LINE, CUBE, ELL, ESS, PYRAMID };

		/**
		 * @brief Default constructor, sets the position to the origin
		 */
		SuperBlock(const SuperBlockType blockType);

		/**
		 * @brief Rotate about x-axis
		 */
		void rotateX();

		/**
		 * @brief Rotate about y-axis
		 */
		void rotateY();

		/**
		 * @brief Rotate about z-axis
		 */
		void rotateZ();
};

#endif
