#include <iostream>
#include "Arena.h"
#include "Player.h"
#include "Defs.h"
#include "TextureFactory.h"


Arena::Arena(void): GameObject()
{	
	center = 0;
}


void Arena::assignToArena(Player *player, SubArena subarena)
{
	playerArenaMap.insert ( std::pair<SubArena, Player*>(subarena, player));
	player->setArena(this);
}

void Arena::submitCommand(Player *player, PlayerCommand command)
{
	std::map<SubArena, Player*>::iterator it;


	//Execute the command on the correct subarena
	for (it = playerArenaMap.begin(); it != playerArenaMap.end(); it++) {
		if ((*it).second->getID() == player->getID()) {

		   SubArena subarena = (*it).first;
		   command.execute(&subArenas[subarena]);

		   //If the command was a drop block, check if we need to clear any layers
		   if (command.getAction() == PlayerCommand::DROP_BLOCK) {
				updateLayers(subarena);
				checkEndCondition();
		   }
		}
	}
}

void Arena::checkEndCondition()
{
	std::map<SubArena, Player*>::iterator it;

	//For each arena
	for (it = playerArenaMap.begin(); it != playerArenaMap.end(); it++) {
		if ( !subArenas[(*it).first].canMoveSuperBlockRelative(Vector(0, 0, 0))) {
			endByPlayerFault((*it).second->getID());
		}
	}
}


void Arena::endByPlayerFault(int playerID)
{
	std::cout << "PLAYER " << playerID << " LOSES!" << std::endl;
	//resolveGameState
}

void Arena::updateLayers(SubArena subarena)
{
	//Get all the full layers
	std::vector<int> filledLayers = subArenas[subarena].getFullLayers();
	
	//And clear them
	if (filledLayers.size() != 0) {

		//Remove the old layers
		subArenas[subarena].removeLayers(filledLayers);

		//Add in the new layers
		subArenas[subarena].addLayersToTop(filledLayers.size());
	}
	
	//Generate a new subarena block
	subArenas[subarena].newSuperBlock();


	//If there were filled layers, we need to do some platform moving
	int layers = filledLayers.size();
	if (layers) {
		SubArena shrinkingArena;
		if (subarena == TOP_ARENA) {
			shrinkingArena = BOTTOM_ARENA;
			center -= layers;
		}
		else {
			shrinkingArena = TOP_ARENA;
			center += layers;
		}
	
		subArenas[subarena].expandSubarena(layers);
		subArenas[shrinkingArena].shrinkSubarena(layers);

		//An arena size change forces the shrinking side to get a new block
		subArenas[shrinkingArena].newSuperBlock();
	}
}


void Arena::reset()
{
	center = 0;
	std::map<SubArena, Player*>::iterator it;

	//Iterate through players and subarenas
	for (it = playerArenaMap.begin(); it != playerArenaMap.end(); it++) {

		subArenas[(*it).first].reset();
		subArenas[(*it).first].newSuperBlock();
	}
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
		subArenas[0].draw(texId);
		glPushMatrix();
			glScalef(1, 1, -1);
			subArenas[1].draw(texId);
		glPopMatrix();
		drawPlateform();
	glPopMatrix();
}

void Arena::draw() const 
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		subArenas[0].draw();
		glPushMatrix();
			glScalef(1, 1, -1);
			subArenas[1].draw();
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

	glPushMatrix();
		glTranslatef(0, 0, center);
		glScalef(1, 1, thinkness);

		//Tile grid
		for (int row = 0; row < dimension; row++) {
			for (int col = 0; col < dimension; col++) {
				float colorR = 1 - color;	color+= step;
				float colorG = color;		color+= step;
				float colorB = 1 - color;	color+= step;

				glPushMatrix();
					glColor3f(colorR, colorG, colorB);
					glTranslatef(row + .5, col + .5, 0);
					glutSolidCube(1);
				glPopMatrix();
			}
		}
	glPopMatrix();
}
