#ifndef SUPER_BLOCK_H
#define SUPER_BLOCK_H
/**
 * @file
 * @brief Contains the SuperBlock class declaration.
 * @author Benjamyn
 */

#include <vector>
#include <functional>
#include "Vector.h"
#include "Block.h"
#include "SimpleRotation.h"

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
		static Block *block; // shared block for drawing
		// location of blocks where the figure is drawn entirely in the positive
		// quadrant
		std::vector<Vector*> blockLocs;

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

	public:
		/**
		 * @brief Different types of super blocks
		 */
		enum SuperBlockType { LINE, CUBE, ELL, ESS, PYRAMID, NUM_SUPER_BLOCK_TYPES };

		/**
		 * @brief Default constructor, sets the position to the origin
		 */
		SuperBlock(const SuperBlockType blockType);

		/**
		 * @brief Copy constructor
		 *
		 * @param other Object to copy from
		 */
		SuperBlock(const SuperBlock& other);

		/**
		 * @brief Constructor, sets the position in addition to setting the block
		 * type
		 */
		SuperBlock(const SuperBlockType blockType, const Vector &v);

		/**
		 * @brief Copy constructor for superblock
		 *
		 * @param rhs Right hand side superblock
		 *
		 * @return *this
		 */
		const SuperBlock& operator=(const SuperBlock& rhs);

		/**
		 * @brief Cleans up the blocks that compose the SuperBlock
		 */
		~SuperBlock();

		/**
		 * @brief Perform the given rotation on the superblock
		 *
		 * @param rotType
		 */
		void rotate(const SimpleRotation::RotationType& rotType);

		/**
		 * @brief Draws the super block with the given color
		 *
		 * @param color A three element color array
		 *
		 * All the Blocks comprising the super block are colored the parameter
		 * color
		 */
		virtual void draw(const float *const color) const;

		/**
		 * @brief Draws the super block with the given texture
		 *
		 * @param texId An OpenGL texture handle
		 *
		 * All the Blocks comprising the super block are textured the parameter
		 * texture
		 */
		virtual void draw(const GLuint texId) const;

		/**
		 * @brief Get a list of the SuperBlock absolute block locations after undergoing the
		 * given translation. The default parameter for the delta is (0, 0, 0).
		 *
		 * @return A vector of translated block locations
		 */
		std::vector<Vector> getBlockLocations(Vector delta = Vector(0, 0, 0)) const;

		/**
		 * @brief Get a list of the SuperBlock absolute block locations after undergoing the
		 * given rotation 
		 *
		 * @return A vector of rotated block locations
		 */
		std::vector<Vector> getBlockLocations(const SimpleRotation::RotationType& rotType) const;

		/**
		 * @brief Get a list of the SuperBlock relative block locations after undergoing the
		 * given translation. The default parameter for the delta is (0, 0, 0).
		 *
		 * @return A vector of translated block locations
		 */
		std::vector<Vector> getBlockLocationsRelative(Vector delta = Vector(0, 0, 0)) const;

		/**
		 * @brief Get a list of the SuperBlock relative block locations after undergoing the
		 * given rotation 
		 *
		 * @return A vector of rotated block locations
		 */
		std::vector<Vector> getBlockLocationsRelative(const SimpleRotation::RotationType& rotType) const;


		/**
		 * @brief Get how many blocks tall the super block is realtive to the super block.
		 *
		 * @return The relative height of the superblock
		 */
		float getRelativeBlockHeight() const;
};

#endif
