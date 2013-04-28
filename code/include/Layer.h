#ifndef LAYER_H
#define LAYER_H
/**
 * @file
 * @brief Contains the Layer class declaration.
 * @author Benjamyn
 */

#include <bitset>
#include "Vector.h"
#include "GameObject.h"
#include "Block.h"
#include <functional>

/**
 * @brief A Layer is composed of a set of Block objects. 
 */
template <int xLength, int yLength>
class Layer: public GameObject {
	private:
		static Block *block; // shared block for drawing

		// Description of bit values:
		//     0) occupied
		//     1) unoccupied
		//
		// The reason behind this is because we can quickly check if all the bits
		// are NOT set via the method "none". The reason this method exists is
		// because it is really quick to test if all the bits are zero i.e. 
		// "0 == x"
		std::bitset <xLength * yLength> unoccupiedLocs;

		/**
		 * @brief Wraps the blockDrawFunc in the translation operations so that the
		 * same operations can be used for the colored and textured block drawing
		 *
		 * @param blockDrawFunc Function that should be called when a block should
		 * be drawn
		 */
		void drawLayerBlocks(std::function<void ()> blockDrawFunc) const;

	public:
		/**
		 * @brief Used to set the status of a location in the layer
		 */
		enum LayerPositionStatus { OCCUPIED, UNOCCUPIED };

		/**
		 * @brief Default constructor, sets the position to the origin and sets the
		 * appropriate dimensions for the layer
		 */
		Layer();

		/**
		 * @brief Constructor that in addition to setting the appropriate
		 * dimensions for the layer, sets the position of the layer
		 *
		 * @param v Position of the layer
		 */
		Layer(const Vector &v);

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
		 * @brief Query whether the layer is completely occupied with blocks
		 *
		 * @return True if layer is full, false otherwise
		 */
		bool isFull() const;

		/**
		 * @brief Query whether the layer is completely empty
		 *
		 * @return True if layer is empty, false otherwise
		 */
		bool isEmpty() const;

		/**
		 * @brief Query if the specific location in the layer is unoccupied
		 *
		 * The function <b>DOES NOT</b> check if the parameters are valid
		 *
		 * @param x x-axis value of the position to check
		 * @param y y-axis value of the position to check
		 *
		 * @return True if the position is unoccupied, false otherwise
		 */
		bool isPosUnoccupied(int x, int y) const;

		/**
		 * @brief Empties the layer of all the filled locations
		 */
		void emptyLayer();

		/**
		 * @brief Fills the layer so all locations are occupied 
		 */
		void fillLayer();

		/**
		 * @brief Marks the given position in this layer
		 *
		 * The function <b>DOES NOT</b> check if the parameters are valid
		 * <b>NOR</b> if we are simply marking an occupied position as occupied
		 * etc.
		 *
		 * @param x x-axis value of the position to mark as occupied
		 * @param y y-axis value of the position to mark as occupied
		 * @param status Set the status of the position
		 */
		void setPosStatus(int x, int y, LayerPositionStatus status);

		/**
		 * @brief Flips the occupied status of the position
		 *
		 * The function <b>DOES NOT</b> check if the parameters are valid
		 * <b>NOR</b> if we are simply marking an occupied position as occupied
		 * etc.
		 *
		 * @param x x-axis value of the position to flip the status
		 * @param y y-axis value of the position to flip the status
		 */
		void flipPosStatus(int x, int y);
};

template <int xLength, int yLength>
Block* Layer<xLength, yLength>::block = new Block(); 

template <int xLength, int yLength>
Layer<xLength, yLength>::Layer(): GameObject()
{
	unoccupiedLocs.set(); // set all the bits to 1 == unoccupied
}

template <int xLength, int yLength>
Layer<xLength, yLength>::Layer(const Vector &v):	GameObject(v)
{
	unoccupiedLocs.set(); // set all the bits to 1 == unoccupied
}

template <int xLength, int yLength>
void Layer<xLength, yLength>::draw(const float *const color) const 
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		// create a lambda function and forward to drawLayerBlocks
		drawLayerBlocks(
				[color,this] () -> void {	this->block->draw(color); }
				);
	glPopMatrix();
}

template <int xLength, int yLength>
void Layer<xLength, yLength>::draw(const GLuint texId) const 
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		// create a lambda function and forward to drawLayerBlocks
		drawLayerBlocks(
				[texId,this] () -> void {	this->block->draw(texId); }
				);
	glPopMatrix();
}

template <int xLength, int yLength>
void Layer<xLength, yLength>::drawLayerBlocks(
		std::function<void ()> blockDrawFunc) const
{
	for (int j = 0; j < yLength; ++j) {
		for (int i = 0; i < xLength; ++i) {
			if (!unoccupiedLocs[j * xLength + i]) {
				glPushMatrix();
					glTranslatef(i, j, 0);
					blockDrawFunc();
				glPopMatrix();
			}
		}
	}
}

template <int xLength, int yLength>
bool Layer<xLength, yLength>::isFull() const
{
	return unoccupiedLocs.none();
}

template <int xLength, int yLength>
bool Layer<xLength, yLength>::isEmpty() const
{
	return unoccupiedLocs.count() == unoccupiedLocs.size();
}

template <int xLength, int yLength>
bool Layer<xLength, yLength>::isPosUnoccupied(int x, int y) const
{
	return unoccupiedLocs[y * xLength + x];
}

template <int xLength, int yLength>
void Layer<xLength, yLength>::emptyLayer()
{
	unoccupiedLocs.set();
}

template <int xLength, int yLength>
void Layer<xLength, yLength>::fillLayer()
{
	unoccupiedLocs.reset();
}

template <int xLength, int yLength>
void Layer<xLength, yLength>::setPosStatus(int x, int y, LayerPositionStatus status)
{
	unoccupiedLocs.set(y * xLength + x, status);
}

template <int xLength, int yLength>
void Layer<xLength, yLength>::flipPosStatus(int x, int y)
{
	unoccupiedLocs.flip(y * xLength + x);
}

#endif
