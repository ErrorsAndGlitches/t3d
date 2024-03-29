#ifndef SUBARENA_H
#define SUBARENA_H
/**
* @file
* @brief Contains the Subarena class declaration.
*/

#include <vector>
#include <algorithm>
#include "Defs.h"
#include "Vector.h"
#include "SuperBlock.h"
#include "SuperBlockFactory.h"
#include "Layer.h"
#include "TextureService.h"


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
	* @brief A vector of all layers
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

	/**
	* @brief Moves the subarena's superblock to the correct start position
	*/
	void moveSuperBlockToStartPosition() const;


	/**
	* @brief Maps the given Z position in absolute coordinates to arena coordinates
	*
	* @param z The z position in absolute coordinated to test
	*
	* @return  The z position in subarena coordinates
	*/
	int mapZToSubarena(int z) const;

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
	* @brief Default subarena draw method
	*/
	virtual void draw() const;

	/**
	* @brief Creates a new, random SuperBlock for this subarena whose initial
	* location is at the center, maximum height of the subarena
	*/
	void newSuperBlock();

	/**
	* @brief Creates a new SuperBlock of type blockType for this subarena
	* whose initial location is at the center, maximum height of the subarena
	*
	* @param blockType SuperBlock type to create
	*/
	void newSuperBlock(SuperBlock::SuperBlockType blockType);

	/**
	 * @brief Get the current SuperBlock type
	 *
	 * @return The SuperBlock's type
	 */
	SuperBlock::SuperBlockType getSuperBlockType() const;

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
	* @brief Move subarena's SuperBlock as low as possible, stopping at
	* another block or the Subarena's floor. Note that this <b>does not</b>
	* insert the SuperBlock into the layers, it only moves the SuperBlock
	*/
	void dropSuperBlock();

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
	* @brief Empties all the layers of the subarena
	*
	*/
	void emptySubarena();

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
	* @brief Add an empty layer to the subarena
	* 
	* @param layerNum The index of the layer to add
	*/
	void addLayer(int layerNum);

	/**
	* @brief Add the specified number of empty layers to the top subarena
	* 
	* @param numLayers The number of layers to add to the top of the subarena
	*/
	void addLayersToTop(int numLayers);

	/**
	* @brief Remove the specified number of layers from the top subarena
	* 
	* @param numLayers The number of layers to remove from the top of the subarena
	*/
	void removeLayersFromTop(int numLayers);

	/**
	* @brief Expand the given subarena by the specificed number of layers
	* 
	* @param layers The number of layers to expand the subarena by.
	*/
	void expandSubarena(int layers);

	/**
	* @brief Shrink the given subarena by the specificed number of layers
	* 
	* @param layers The number of layers to shrink the subarena by.
	*/
	void shrinkSubarena(int layers);


	/**
	* @brief Remove the given layer from the subarena
	*
	* @param layerNum The number of the layer to remove
	*/
	void removeLayer(int layerNum);

	/**
	* @brief Remove the given layers from the subarena
	*
	* @param layerNum The numbers of the layers to remove
	*/
	void removeLayers(std::vector<int> layerNums);

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

	/**
	* @brief Reset the subarena
	*/
	void reset();
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
	superBlock(sbFactory->getSuperBlock()), drawSuperBlock(true)
{
	// add layers
	for (int i = 0; i < height; ++i) {
		layers->push_back(new Layer<length, length>(Vector(0, 0, i)));
	}

	// add superblock
	moveSuperBlockToStartPosition();
}

template <int length, int height>
void Subarena<length, height>::draw(const float *const color) const 
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	// draw each layer
	for (Layer<length, length> *layer : *layers) {
		layer->draw(color);
	}
	// draw the SuperBlock
	superBlock->draw(color);
	glPopMatrix();
}

template <int length, int height>
void Subarena<length, height>::draw() const 
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	// draw each layer
	for (Layer<length, length> *layer : *layers) {
		layer->draw(TextureService::getTextureServiceInstance()
			->getTexture(TextureService::GREY_SQUARE_FACE));
	}
	// draw the SuperBlock
	superBlock->draw();
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
void Subarena<length, height>::moveSuperBlockToStartPosition() const
{
	//Vertical block offset is how far down from the top of the subarena we should place the block
	int blockVertOffset = superBlock->getRelativeBlockHeight();
	superBlock->setPos(Vector(length / 2, length / 2, height - blockVertOffset));
}

template <int length, int height>
void Subarena<length, height>::newSuperBlock()
{
	delete(superBlock);
	superBlock = sbFactory->getSuperBlock();
	moveSuperBlockToStartPosition();
}

template <int length, int height>
void Subarena<length, height>::newSuperBlock(SuperBlock::SuperBlockType blockType)
{
	delete(superBlock);
	superBlock = sbFactory->getSuperBlock(blockType);
	moveSuperBlockToStartPosition();
}

template <int length, int height>
SuperBlock::SuperBlockType Subarena<length, height>::getSuperBlockType() const
{
	return superBlock->getSuperBlockType();
}

template <int length, int height>
void Subarena<length, height>::setDrawSuperBlock(bool drawSuperBlock)
{
	this->drawSuperBlock = drawSuperBlock;
}

template <int length, int height>
bool Subarena<length, height>::isLocationEmpty(const Vector& loc) const
{
	int adjustedZ = mapZToSubarena(loc.z);
	if (adjustedZ < 0 
		|| loc.x >= length || loc.x < 0
		|| loc.y >= length || loc.y < 0) { return false; }
	if (adjustedZ >= layers->size()) { return true; }

	if ((*layers)[adjustedZ]->isPosUnoccupied(loc.x, loc.y)) { return true; }
	else { return false; }
}

template <int length, int height>
int Subarena<length, height>::mapZToSubarena(int z) const
{
	return z + (layers->size() - height);
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
void Subarena<length, height>::dropSuperBlock()
{

	//Test whether the superblock can drop by delta number of layers until it cannot
	int delta = 0;
	while (canMoveSuperBlockRelative(Vector(0, 0, delta))) {
		delta--;
	}

	//Then commit to the last layer where it could drop to 
	moveSuperBlockRelative(Vector(0, 0, delta + 1));
}

template <int length, int height>
void Subarena<length, height>::insertSuperBlockIntoLayers() 
{
	for (const Vector& vec : superBlock->getBlockLocations()) {
		int adjustedZ = mapZToSubarena(vec.z);
		if (adjustedZ < layers->size()) {
 			(*layers)[adjustedZ]->setPosStatus(vec.x, vec.y, Layer<length, length>::LayerPositionStatus::OCCUPIED);
		}
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

template <int length, int height>
void Subarena<length, height>::addLayer(int layerNum)
{
	layers->insert(layers->begin() + layerNum, new Layer<length, length>());
}


template <int length, int height>
void Subarena<length, height>::emptySubarena()
{
	for (int i = 0; i < layers->size(); ++i) {
		(*layers)[i]->emptyLayer();
	}
}

template <int length, int height>
void Subarena<length, height>::removeLayer(int layerNum)
{
	delete((*layers)[layerNum]);
	layers->erase(layers->begin() + layerNum);
}

template <int length, int height>
void Subarena<length, height>::removeLayers(std::vector<int> layerNums)
{
	//Maintain a layer offset so that we know how much to shift each layer after a deletion, 
	//and so we reference the correct layer after a deletion
	int offset = 0;

	int arenaSize = layers->size();

	//For each layer slot of the subarena
	for (int layerNum = 0; layerNum < arenaSize; layerNum++){

		//Calculate the adjusted layer we are looking at taking into account deleted layers that came before it.
		int adjustedLayerNum = layerNum - offset;

		//If the layer is to be deleted then delete it, erase it from the layer stack, and update the the current offset
		if (std::find(layerNums.begin(), layerNums.end(), layerNum) != layerNums.end()) {
			delete((*layers)[adjustedLayerNum]);
			layers->erase(layers->begin() + adjustedLayerNum);
			offset++;											
		}

		//Otherwise the position of the current layer by the offset
		else {
			(*layers)[adjustedLayerNum]->updateRelaPos(Vector(0, 0, -offset));
		}
	}
}

template <int length, int height>
void Subarena<length, height>::reset()
{
	layers->clear();

	// add layers
	for (int i = 0; i < height; ++i) {
		layers->push_back(new Layer<length, length>(Vector(0, 0, i)));
	}
}

template <int length, int height>
void Subarena<length, height>::addLayersToTop(int numLayers)
{
	int top = layers->back()->getPos().z;
	
	//Add numLayers layers to the vector of layers.
	while(numLayers > 0) {
		layers->push_back(new Layer<length, length>(Vector(0, 0, ++top)));
		numLayers--;
	}
}


template <int length, int height>
void Subarena<length, height>::removeLayersFromTop(int numLayers)
{
	
	//Add numLayers layers to the vector of layers.
	while(numLayers > 0) {
		removeLayer(layers->size() - 1);
		numLayers--;
	}
}

template <int length, int height>
void Subarena<length, height>::expandSubarena(int numLayers)
{
	//Add numLayers layers to the vector of layers.
	addLayersToTop(numLayers);

	// Adjt layer height
	for (int i = 0; i < layers->size(); ++i) {
		(*layers)[i]->updateRelaPos(Vector(0, 0, -numLayers));
	}
}

template <int length, int height>
void Subarena<length, height>::shrinkSubarena(int numLayers)
{
	//Remove numLayers layers from the vector of layers.
	removeLayersFromTop(numLayers);

	// Adjt layer height
	for (int i = 0; i < layers->size(); ++i) {
		(*layers)[i]->updateRelaPos(Vector(0, 0, numLayers));
	}
}


#endif
