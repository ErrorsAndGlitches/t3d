#include "SuperBlock.h"
#include <cstdlib>
#include <iostream>
#include <GL/gl.h>

Block* SuperBlock::block = new Block(); 

SuperBlock::~SuperBlock()
{
	for (Vector *blockLoc : blockLocs) {
		delete(blockLoc);
	}

	blockLocs.clear();
}

SuperBlock::SuperBlock(const SuperBlockType blockType): GameObject()
{
	switch(blockType)
	{
		case LINE:
			createLineSuperBlock();
			break;
		case CUBE:
			createCubeSuperBlock();
			break;
		case ELL:
			createEllSuperBlock();
			break;
		case ESS:
			createEssSuperBlock();
			break;
		case PYRAMID:
			createPyramidSuperBlock();
			break;
		default:
			std::cout << "NOT A VALID SUPER BLOCK TYPE: (" 
								<< blockType 
								<< ")" 
								<< std::endl;
			std::exit(-1);
			break;
	}
}

SuperBlock::SuperBlock(const SuperBlock& other): GameObject()
{
	for (Vector *blockLoc : other.blockLocs) {
		blockLocs.push_back(new Vector(*blockLoc));
	}
}

const SuperBlock& SuperBlock::operator=(const SuperBlock& rhs)
{
	for (Vector *blockLoc : blockLocs) {
		delete(blockLoc);
	}

	blockLocs.clear();

	for (const Vector& vec : rhs.getBlockLocations()) {
		blockLocs.push_back(new Vector(vec));
	}

	return *this;
}

void SuperBlock::createLineSuperBlock()
{
	blockLocs.push_back(new Vector(0, 0, -2));
	blockLocs.push_back(new Vector(0, 0, -1));
	blockLocs.push_back(new Vector(0, 0, 0));
	blockLocs.push_back(new Vector(0, 0, 1));
}

void SuperBlock::createCubeSuperBlock()
{
	blockLocs.push_back(new Vector(0, 0, 0));
	blockLocs.push_back(new Vector(0, 1, 0));
	blockLocs.push_back(new Vector(1, 1, 0));
	blockLocs.push_back(new Vector(1, 0, 0));

	blockLocs.push_back(new Vector(0, 0, 1));
	blockLocs.push_back(new Vector(0, 1, 1));
	blockLocs.push_back(new Vector(1, 1, 1));
	blockLocs.push_back(new Vector(1, 0, 1));
}

void SuperBlock::createEllSuperBlock()
{
	blockLocs.push_back(new Vector(0, 0, 0));
	blockLocs.push_back(new Vector(0, 0, 1));
	blockLocs.push_back(new Vector(1, 0, 0));
	blockLocs.push_back(new Vector(2, 0, 0));
}

void SuperBlock::createEssSuperBlock()
{
	blockLocs.push_back(new Vector(-1, 0, 0));
	blockLocs.push_back(new Vector(0, 0, 0));
	blockLocs.push_back(new Vector(0, 0, 1));
	blockLocs.push_back(new Vector(1, 0, 1));
}

void SuperBlock::createPyramidSuperBlock()
{
	blockLocs.push_back(new Vector(0, 0, 0));
	blockLocs.push_back(new Vector(1, 0, 0));
	blockLocs.push_back(new Vector(-1, 0, 0));
	blockLocs.push_back(new Vector(0, 1, 0));
	blockLocs.push_back(new Vector(0, -1, 0));
	blockLocs.push_back(new Vector(0, 0, 1));
}

void SuperBlock::draw(const float *const color) const 
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		// create a lambda function and forward to drawBlockList
		drawBlockList(
				[color,this] () -> void {	this->block->draw(color); }
				);
	glPopMatrix();
}

void SuperBlock::draw(const GLuint texId) const 
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		// create a lambda function and forward to drawBlockList
		drawBlockList(
				[texId,this] () -> void {	this->block->draw(texId); }
				);
	glPopMatrix();
}

void SuperBlock::drawBlockList(std::function<void ()> blockDrawFunc) const
{
	// draw each of the blocks
	for (const Vector *blockLoc : blockLocs) {
		glPushMatrix();
			glTranslatef(blockLoc->x, blockLoc->y, blockLoc->z);
			blockDrawFunc();
		glPopMatrix();
	}
}	

void SuperBlock::rotate(const SimpleRotation::RotationType& rotType)
{
	for (Vector* blockLoc : blockLocs) {
		SimpleRotation::rotate(*blockLoc, rotType);
	}
}

std::vector<Vector> SuperBlock::getBlockLocations() const
{
	std::vector<Vector> blPosits;

	for (Vector *vec : blockLocs) {
		blPosits.push_back(*vec);
	}

	return blPosits;
}

std::vector<Vector> SuperBlock::getBlockLocations(const Vector& delta) const
{
	std::vector<Vector> blPosits;

	for (Vector *vec : blockLocs) {
		blPosits.push_back(*vec + delta);
	}

	return blPosits;
}

std::vector<Vector> SuperBlock::getBlockLocations(const SimpleRotation::RotationType& rotType) const
{
	std::vector<Vector> blPosits;

	for (const Vector *vec : blockLocs) {
		blPosits.push_back(SimpleRotation::rotate(*vec, rotType));
	}

	return blPosits;
}
