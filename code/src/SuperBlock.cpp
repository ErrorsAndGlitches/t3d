#include "SuperBlock.h"
#include <cstdlib>
#include <iostream>
#include <GL/gl.h>

Block* SuperBlock::block = new Block(); 

SuperBlock::SuperBlock(const SuperBlockType blockType)
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

void SuperBlock::createLineSuperBlock()
{
	comToOrigin.setPos(-0.5, -0.5, -2);

	blockLocs.push_back(Vector(0, 0, 0));
	blockLocs.push_back(Vector(0, 0, 1));
	blockLocs.push_back(Vector(0, 0, 2));
	blockLocs.push_back(Vector(0, 0, 3));
}

void SuperBlock::createCubeSuperBlock()
{
	comToOrigin.setPos(-0.5, -0.5, -1);

	blockLocs.push_back(Vector(0, 0, 0));
	blockLocs.push_back(Vector(0, 1, 0));
	blockLocs.push_back(Vector(1, 1, 0));
	blockLocs.push_back(Vector(1, 0, 0));

	blockLocs.push_back(Vector(0, 0, 1));
	blockLocs.push_back(Vector(0, 1, 1));
	blockLocs.push_back(Vector(1, 1, 1));
	blockLocs.push_back(Vector(1, 0, 1));
}

void SuperBlock::createEllSuperBlock()
{
	comToOrigin.setPos(-1.5, -0.5, -1);

	blockLocs.push_back(Vector(0, 0, 0));
	blockLocs.push_back(Vector(0, 0, 1));
	blockLocs.push_back(Vector(0, 1, 0));
	blockLocs.push_back(Vector(0, 2, 0));
}

void SuperBlock::createEssSuperBlock()
{
	comToOrigin.setPos(-1.5, -0.5, -1);

	blockLocs.push_back(Vector(0, 0, 0));
	blockLocs.push_back(Vector(1, 0, 0));
	blockLocs.push_back(Vector(1, 0, 1));
	blockLocs.push_back(Vector(2, 0, 1));
}

void SuperBlock::createPyramidSuperBlock()
{
	comToOrigin.setPos(-1.5, -1.5, -1);

	blockLocs.push_back(Vector(1, 0, 0));
	blockLocs.push_back(Vector(1, 1, 0));
	blockLocs.push_back(Vector(1, 2, 0));
	blockLocs.push_back(Vector(2, 1, 0));
	blockLocs.push_back(Vector(0, 1, 0));
	blockLocs.push_back(Vector(1, 1, 1));
}

void SuperBlock::drawColoredGameObject() const
{
	// create a lambda function and forward to drawBlockList
	drawBlockList(
			[this] () -> void {	this->block->drawColoredGameObject(); }
			);
}

void SuperBlock::drawTexturedGameObject() const
{
	// create a lambda function and forward to drawBlockList
	drawBlockList(
			[this] () -> void {	this->block->drawTexturedGameObject(); }
			);
}

void SuperBlock::drawBlockList(std::function<void ()> blockDrawFunc) const
{
	// translate to origin
	glTranslatef(-comToOrigin.x, -comToOrigin.y, -comToOrigin.z);	
		// perform rotations about COM
		//    need to do rotations in reverse!
		for (auto it = rotations.rbegin(); it != rotations.rend(); ++it) {
			switch (*it) {
				case ROT_X:
					glRotatef(90, 1, 0, 0);
					break;
				case ROT_Y:
					glRotatef(90, 0, 1, 0);
					break;
				case ROT_Z:
					glRotatef(90, 0, 0, 1);
					break;
			}
		}
	// return back to original position	
	glTranslatef(comToOrigin.x, comToOrigin.y, comToOrigin.z);	

	// draw each of the blocks
	for (Vector blockLoc : blockLocs) {
		glPushMatrix();
			glTranslatef(blockLoc.x, blockLoc.y, blockLoc.z);
			blockDrawFunc();
		glPopMatrix();
	}
}	

void SuperBlock::rotateX()
{
	rotations.push_back(ROT_X);
}

void SuperBlock::rotateY()
{
	rotations.push_back(ROT_Y);
}

void SuperBlock::rotateZ()
{
	rotations.push_back(ROT_Z);
}
