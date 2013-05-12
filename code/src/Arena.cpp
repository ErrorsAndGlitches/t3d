#include <iostream>
#include "Arena.h"
#include "Player.h"
#include "Defs.h"
#include "TextureFactory.h"


Arena::Arena(void): GameObject()
{
	
}

void Arena::init() 
{
	textID_RED = TextureFactory::getTextureHandle(RED_SQUARE_FILENAME);	
	textID_BLUE = TextureFactory::getTextureHandle(BLUE_SQUARE_FILENAME);	
}

void Arena::assignToArena(Player *player, SubArena subarena)
{
	playerArenaMap.insert ( std::pair<SubArena,int>(subarena, player->getID()));
	player->setArena(this);
}

void Arena::submitCommand(Player *player, PlayerCommand command)
{
	std::map<SubArena, int>::iterator it;

	//Execute the command on the correct subarena
	for (it = playerArenaMap.begin(); it != playerArenaMap.end(); it++) {
		if ((*it).second == player->getID()) {
		   SubArena subarena = (*it).first;
		   command.execute(&subArenas[subarena]);

		   //If the command was a drop block, check if we need to clear any layers
		   if (command.getAction() == PlayerCommand::DROP_BLOCK) {
				clearFullLayers(subarena);
		   }
	   }
	}
}

void  Arena::clearFullLayers(SubArena subarena)
{
	//Get all the full layers
	std::vector<int> filledLayers = subArenas[subarena].getFullLayers();
	

	if (filledLayers.size() != 0) {

		//Remove the old layers
		subArenas[subarena].removeLayers(filledLayers);

		//Add in the new layers
		subArenas[subarena].addLayersToTop(filledLayers.size());
	}
	//Make a new block
	subArenas[subarena].newSuperBlock();
}

void Arena::draw(const float *const color) const 
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		subArenas[0].draw(color);
		glPushMatrix();
			glScalef(1, 1, -1);
			subArenas[1].draw(color);
		glPopMatrix();
		drawPlateform();
	glPopMatrix();
}

void Arena::draw(const GLuint texId) const 
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		subArenas[0].draw(textID_BLUE);
		glPushMatrix();
			glScalef(1, 1, -1);
			subArenas[1].draw(textID_BLUE);
		glPopMatrix();
		drawPlateform();
	glPopMatrix();
}

void Arena::drawPlateform() const
{
	float thinkness = .1;	//How think the plateform will be
	float color = 0;
	int dimension = DEFAULT_SUBARENA_LENGTH;
	float step = 1.0 / (dimension * dimension * 3);	//colloring pattern offsets

	glBindTexture(GL_TEXTURE_2D, textID_RED);
	glEnable(GL_TEXTURE_2D);


	glPushMatrix();
		glScalef(1, 1, thinkness);

		//Tile grid
		for (int row = 0; row < dimension; row++) {
			for (int col = 0; col < dimension; col++) {
				//float colorR = color;  color+= step;
				//float colorG = color;  color+= step;
				//float colorB = color;  color+= step;

				glPushMatrix();
					//glColor3f(colorR, colorG, colorB);
					glTranslatef(row , col, -.01);
					glPushMatrix();

						glBegin(GL_QUADS); //top
							glTexCoord2f(0,0); glVertex3f(0, 0, 1);
							glTexCoord2f(0,1); glVertex3f(0, 1, 1);
							glTexCoord2f(1,1); glVertex3f(1, 1, 1);
							glTexCoord2f(1,0); glVertex3f(1, 0, 1);
						glEnd(); 
		

						glBegin(GL_QUADS); //North
							glTexCoord2f(0,0); glVertex3f(1, 0, 1);
							glTexCoord2f(0,1); glVertex3f(0, 0, 1);
							glTexCoord2f(1,1); glVertex3f(0, 0, 0);
							glTexCoord2f(1,0); glVertex3f(1, 0, 0);
						glEnd();


						glBegin(GL_QUADS); //South
							glTexCoord2f(0,0); glVertex3f(1, 1, 1);
							glTexCoord2f(0,1); glVertex3f(0, 1, 1);
							glTexCoord2f(1,1); glVertex3f(0, 1, 0);
							glTexCoord2f(1,0); glVertex3f(1, 1, 0);
						glEnd();

						glBegin(GL_QUADS); //East
							glTexCoord2f(0,0); glVertex3f(1, 1, 1);
							glTexCoord2f(0,1); glVertex3f(1, 0, 1);
							glTexCoord2f(1,1); glVertex3f(1, 0, 0);
							glTexCoord2f(1,0); glVertex3f(1, 1, 0);
						glEnd();

						glBegin(GL_QUADS); //West
							glTexCoord2f(0,0); glVertex3f(0, 1, 1);
							glTexCoord2f(0,1); glVertex3f(0, 0, 1);
							glTexCoord2f(1,1); glVertex3f(0, 0, 0);
							glTexCoord2f(1,0); glVertex3f(0, 1, 0);
						glEnd();

						glBegin(GL_QUADS); //bottom
							glTexCoord2f(0,0); glVertex3f(0, 0, 0);
							glTexCoord2f(0,1); glVertex3f(0, 1, 0);
							glTexCoord2f(1,1); glVertex3f(1, 1, 0);
							glTexCoord2f(1,0); glVertex3f(1, 0, 0);
						glEnd();
					glPopMatrix();
				glPopMatrix();
			}
		}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
