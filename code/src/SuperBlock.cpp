#include "SuperBlock.h"
#include <cstdlib>
#include <iostream>
#include <GL/gl.h>

Block* SuperBlock::block = new Block(); 

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

void SuperBlock::createLineSuperBlock()
{
	rotPtToOrigin.setPos(-0.5, -0.5, -1.5);

	blockLocs.push_back(Vector(0, 0, 0));
	blockLocs.push_back(Vector(0, 0, 1));
	blockLocs.push_back(Vector(0, 0, 2));
	blockLocs.push_back(Vector(0, 0, 3));
}

void SuperBlock::createCubeSuperBlock()
{
	rotPtToOrigin.setPos(-1, -1, -1);

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
	rotPtToOrigin.setPos(-0.5, -0.5, -0.5);

	blockLocs.push_back(Vector(0, 0, 0));
	blockLocs.push_back(Vector(0, 0, 1));
	blockLocs.push_back(Vector(1, 0, 0));
	blockLocs.push_back(Vector(2, 0, 0));
}

void SuperBlock::createEssSuperBlock()
{
	rotPtToOrigin.setPos(-1.5, -0.5, -0.5);

	blockLocs.push_back(Vector(0, 0, 0));
	blockLocs.push_back(Vector(1, 0, 0));
	blockLocs.push_back(Vector(1, 0, 1));
	blockLocs.push_back(Vector(2, 0, 1));
}

void SuperBlock::createPyramidSuperBlock()
{
	rotPtToOrigin.setPos(-1.5, -1.5, -0.5);

	blockLocs.push_back(Vector(1, 0, 0));
	blockLocs.push_back(Vector(1, 1, 0));
	blockLocs.push_back(Vector(1, 2, 0));
	blockLocs.push_back(Vector(2, 1, 0));
	blockLocs.push_back(Vector(0, 1, 0));
	blockLocs.push_back(Vector(1, 1, 1));
}

void SuperBlock::draw(const float *const color) const 
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		glColor3fv(color);
			// create a lambda function and forward to drawBlockList
			drawBlockList(
					[color,this] () -> void {	this->block->draw(color); }
					);
		glColor3fv(WHITE); // so we don't have a tint for future texture draws
	glPopMatrix();
}

void SuperBlock::draw(const GLuint texId) const 
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);

		// tell opengl which texture we want to use
		glBindTexture(GL_TEXTURE_2D, texId);
		glEnable(GL_TEXTURE_2D);
			// create a lambda function and forward to drawBlockList
			drawBlockList(
					[texId,this] () -> void {	this->block->draw(texId); }
					);
		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void SuperBlock::drawBlockList(std::function<void ()> blockDrawFunc) const
{
	// translate to origin
	glTranslatef(-rotPtToOrigin.x, -rotPtToOrigin.y, -rotPtToOrigin.z);	
		// perform rotations about rotation point
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
	glTranslatef(rotPtToOrigin.x, rotPtToOrigin.y, rotPtToOrigin.z);	

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
