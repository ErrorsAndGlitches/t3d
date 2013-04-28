#ifndef SUBARENA_H
#define SUBARENA_H
/**
 * @file
 * @brief Contains the Subarena class declaration.
 */

#include <vector>
#include "Defs.h"
#include "Vector.h"
#include "SuperBlock.h"
#include "SuperBlockFactory.h"
#include "Layer.h"

/**
 * @brief A Subarena encapsulates and controls all the objects in each 
 * player's subarena. 
 *
 * The objects in each subarena include the current SuperBlock, its
 * layers, and walls.
 *
 * Users are able to interact with the objects in the subarena through its
 * interface. They are also able to query whether certains operations are
 * valid, such as rotating a superblock, and then to commit the operation 
 * if possible.
 *
 * The default setting is to draw the SuperBlock.
 */
template <int length = DEFAULT_SUBARENA_LENGTH, int height = DEFAULT_SUBARENA_HEIGHT>
class Subarena: public GameObject {
	private:
		/**
		 * @brief A vector of all 
		 */
		std::vector< Layer<length, length>* > *layers;

		/**
		 * @brief Current SuperBlock falling in the player's subarena
		 */
		SuperBlockFactory *sbFactory;
		SuperBlock *superBlock;
		bool drawSuperBlock;

		/**
		 * @brief Query whether the given vector of locations is empty
		 *
		 * @param locs The vector of locations to test
		 *
		 * @return True if all of the locations are empty, false otherwise
		 */
		bool testBlockPositionsEmpty(const std::vector<Vector>& locs) const;

	public:
		/**
		 * @brief Constructor that allows the length of the subarena to be
		 * defined.
		 *
		 * The constructor generates a SuperBlock for the Subarena as a side
		 * effect.
		 */
		Subarena();

		/**
		 * @brief Draws the layer with the given color
		 *
		 * @param color A three element color array
		 *
		 * All the Blocks comprising the layer are colored the parameter
		 * color
		 */
		virtual void draw(const float *const color) const;

		/**
		 * @brief Draws the layer with the given texture
		 *
		 * @param texId An OpenGL texture handle
		 *
		 * All the Blocks comprising the layer are textured the parameter
		 * texture
		 */
		virtual void draw(const GLuint texId) const;

		/**
		 * @brief Creates a new SuperBlock for this subarena whose initial location
		 * is at the center, maximum height of the subarena
		 */
		void newSuperBlock();

		/**
		 * @brief Sets whether the SuperBlock should be drawn when the subarena is drawn
		 *
		 * @param drawSuperBlock True/false on whether to draw SuperBlock
		 */
		void setDrawSuperBlock(bool drawSuperBlock);

		/**
		 * @brief Query if the given location in the subarena is empty
		 *
		 * Locations beyond the borders of the subarena are considered not empty.
		 *
		 * @param loc Location to query in the subarena
		 *
		 * @return True if the location is empty, false otherwise
		 */
		bool isLocationEmpty(const Vector& loc) const;

		/**
		 * @brief Ask the subarena whether moving the SuperBlock by the given delta
		 * distance causes it to hit another object
		 *
		 * @param delta The delta distance to move the SuperBlock
		 *
		 * @return True if the SuperBlock can successfully be moved and false
		 * otherwise. 
		 */
		bool canMoveSuperBlockRelative(const Vector& delta) const;

		/**
		 * @brief Move the Superblock by the given delta
		 *
		 * @param delta The delta distance to move the SuperBlock
		 */
		void moveSuperBlockRelative(const Vector& delta);

		/**
		 * @brief Inserts the subarena's SuperBlock into the layers based on its blocks
		 * current position
		 *
		 * This method does not generate a new SuperBlock. The SuperBlock still remains
		 * at its current position (which is now occupied by the inserted blocks as
		 * well).
		 */
		void insertSuperBlockIntoLayers();

		/**
		 * @brief Get a list of the layers that are full
		 *
		 * @return A vector of the filled layers
		 */
		std::vector<int> getFullLayers() const;

		/**
		 * @brief Query whether the given layer is filled. 
		 *
		 * The bottom layer is at index 0 and increments upwards to the current
		 * height from there. This method does not check if the input layer is a
		 * valid layer number.
		 *
		 * @param layerNum The layer number 
		 *
		 * @return True if the layer is filled, false otherwise
		 */
		bool isLayerFull(int layerNum) const;

		/**
		 * @brief Query whether the given layer is empty. 
		 *
		 * The bottom layer is at index 0 and increments upwards to the current
		 * height from there. This method does not check if the input layer is a
		 * valid layer number.
		 *
		 * @param layerNum The layer number 
		 *
		 * @return True if the layer is empty, false otherwise
		 */
		bool isLayerEmpty(int layerNum) const;

		/**
		 * @brief Query whether it is possible to rotate the subarena's superblock
		 *
		 * @param rotType The rotation to apply to the superblock
		 *
		 * @return True if the superblock can successfully be rotated, false
		 * otherwise
		 */
		bool canRotateSuperBlock(const SimpleRotation::RotationType& rotType) const;

		/**
		 * @brief Rotate the superblock
		 *
		 * @param rotType The rotation to apply to the superblock
		 */
		void rotateSuperBlock(const SimpleRotation::RotationType& rotType);
};

template <int length, int height>
bool Subarena<length, height>::testBlockPositionsEmpty(const std::vector<Vector>& locs) const
{
	bool canMove = true;
	for (const Vector& vec : locs) {
		if (!isLocationEmpty(vec)) {
			canMove = false;
			break;
		}
	}

	return canMove;
}

template <int length, int height>
Subarena<length, height>::Subarena(): GameObject(), 
	layers(new std::vector< Layer<length, length>* >()),
	sbFactory(SuperBlockFactory::getSuperBlockFactoryInstance()), 
	superBlock(sbFactory->getRandomSuperBlock()), drawSuperBlock(true)
{
	// add layers
	for (int i = 0; i < height; ++i) {
		layers->push_back(new Layer<length, length>());
	}

	// add superblock
	superBlock->setPos(Vector(length / 2, length / 2, height));
}

template <int length, int height>
void Subarena<length, height>::draw(const float *const color) const 
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		// draw each layer
		for (Layer<length, length> *layer : *layers)
			layer->draw(color);
		// draw the SuperBlock
		superBlock->draw(color);
	glPopMatrix();
}

template <int length, int height>
void Subarena<length, height>::draw(const GLuint texId) const 
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		// draw each layer
		for (Layer<length, length> *layer : *layers)
			layer->draw(texId);
		superBlock->draw(texId);
	glPopMatrix();
}

template <int length, int height>
void Subarena<length, height>::newSuperBlock()
{
	delete(superBlock);
	superBlock = sbFactory->getRandomSuperBlock();
	superBlock->setPos(Vector(length / 2, length / 2, height));
}

template <int length, int height>
void Subarena<length, height>::setDrawSuperBlock(bool drawSuperBlock)
{
	this->drawSuperBlock = drawSuperBlock;
}

template <int length, int height>
bool Subarena<length, height>::isLocationEmpty(const Vector& loc) const
{
	if (loc.z > layers->size() || loc.z < 0 
			|| loc.x > length || loc.x < 0
			|| loc.y > length || loc.y < 0) { return false; }

	if ((*layers)[loc.z]->isPosUnoccupied(loc.x, loc.y)) { return true; }
	else { return false; }
}

template <int length, int height>
bool Subarena<length, height>::canMoveSuperBlockRelative(const Vector& delta) const
{
	// get block locations and use a rvalue reference (so temporary doesn't need
	// to be copied)
	std::vector<Vector>&& updatedLocations = superBlock->getBlockLocations(delta);
	return testBlockPositionsEmpty(updatedLocations);
}

template <int length, int height>
void Subarena<length, height>::moveSuperBlockRelative(const Vector& delta)
{
	superBlock->updateRelaPos(delta);
}

template <int length, int height>
void Subarena<length, height>::insertSuperBlockIntoLayers() 
{
	for (const Vector& vec : superBlock->getBlockLocations()) {
		(*layers)[vec.z]->setPosStatus(vec.x, vec.y, Layer<length, length>::LayerPositionStatus::OCCUPIED);
	}
}

template <int length, int height>
std::vector<int> Subarena<length, height>::getFullLayers() const
{
	std::vector<int> filledLayers;

	for (int i = 0; i < layers->size(); ++i) {
		if ((*layers)[i]->isFull()) {
			filledLayers.push_back(i);
		}
	}

	return filledLayers;
}

template <int length, int height>
bool Subarena<length, height>::isLayerFull(int layerNum) const
{
	return (*layers)[layerNum]->isFull();
}

template <int length, int height>
bool Subarena<length, height>::isLayerEmpty(int layerNum) const
{
	return (*layers)[layerNum]->isEmpty();
}

template <int length, int height>
bool Subarena<length, height>::canRotateSuperBlock(const SimpleRotation::RotationType& rotType) const
{
	// get block locations and use a rvalue reference (so temporary doesn't need
	// to be copied)
	std::vector<Vector>&& updatedLocations = superBlock->getBlockLocations(rotType);
	return testBlockPositionsEmpty(updatedLocations);
}

template <int length, int height>
void Subarena<length, height>::rotateSuperBlock(const SimpleRotation::RotationType& rotType)
{
	superBlock->rotate(rotType);
}

#endif
