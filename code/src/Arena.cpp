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
	command.execute(&subArenas[TOP_ARENA]);

	//If the command was a drop block, check if we need to clear any layers
	if (command.getAction() == PlayerCommand::DROP_BLOCK) {
		updateLayers(TOP_ARENA); // this generates a new superblock
		subArenas[TOP_ARENA].newSuperBlock();
		checkEndCondition();

		// need to submit the command second because if it is a DROP_BLOCK or something
		// that changes the SuperBlockType, then the Subarena will not have gotten
		// the new SuperBlockType until after the above code
		submitNetworkCommandFunc(command);
		submitNetworkCommandFunc(PlayerCommand(PlayerCommand::Action::TEST_NEW_BLOCK));
	}
	else if (PlayerCommand::Action::TEST_NEW_BLOCK == command.getAction()) {
		submitNetworkCommandFunc(PlayerCommand(PlayerCommand::Action::TEST_NEW_BLOCK));
	}
	else {
		submitNetworkCommandFunc(command);
	}
}

SuperBlock::SuperBlockType Arena::getSuperBlockType() const
{
	return subArenas[TOP_ARENA].getSuperBlockType();
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
	updateWorldStateFunc(GameState::LOST);
	submitNetworkCommandFunc(PlayerCommand::Action::I_LOST);
}

bool Arena::updateLayers(SubArena subarena)
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
		return true;
	}
	else {
		return false;
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

		glPushMatrix();
			glTranslatef(DEFAULT_SUBARENA_LENGTH / 2.0f, DEFAULT_SUBARENA_LENGTH / 2.0f, 0.0f);
			drawZAxis();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(DEFAULT_SUBARENA_LENGTH, DEFAULT_SUBARENA_LENGTH, 0.0f);
			drawBoundingBox();
		glPopMatrix();
	glPopMatrix();
}

void Arena::drawZAxis() const
{
	// draw some axis
	glBegin(GL_LINES);
		// z axis
		glColor4f(0, 0, 1, 1);
		glVertex3f(0, 0, -DEFAULT_SUBARENA_HEIGHT);
		glVertex3f(0, 0, DEFAULT_SUBARENA_HEIGHT);
	glEnd();
}

void Arena::drawBoundingBox() const
{
	glBegin(GL_LINE_STRIP);
		// four corner vertical lines
		glColor4f(0, 0, 1, 1);
		glVertex3f(0.0f, 
							 0.0f, 
							 DEFAULT_SUBARENA_HEIGHT);
		glVertex3f(0.0f, 
							 0.0f, 
							 -DEFAULT_SUBARENA_HEIGHT);
		glVertex3f(0.0f, 
							 -DEFAULT_SUBARENA_LENGTH, 
							 -DEFAULT_SUBARENA_HEIGHT);
		glVertex3f(0.0f, 
							 -DEFAULT_SUBARENA_LENGTH, 
							 DEFAULT_SUBARENA_HEIGHT);
		glVertex3f(0.0f, 
							 0.0f, 
							 DEFAULT_SUBARENA_HEIGHT);

		glVertex3f(-DEFAULT_SUBARENA_LENGTH, 
							 0.0f, 
							 DEFAULT_SUBARENA_HEIGHT);
		glVertex3f(-DEFAULT_SUBARENA_LENGTH, 
							 0.0f, 
							 -DEFAULT_SUBARENA_HEIGHT);
		glVertex3f(-DEFAULT_SUBARENA_LENGTH, 
							 -DEFAULT_SUBARENA_LENGTH, 
							 -DEFAULT_SUBARENA_HEIGHT);
		glVertex3f(-DEFAULT_SUBARENA_LENGTH, 
							 -DEFAULT_SUBARENA_LENGTH, 
							 DEFAULT_SUBARENA_HEIGHT);
		glVertex3f(-DEFAULT_SUBARENA_LENGTH, 
							 0.0f, 
							 DEFAULT_SUBARENA_HEIGHT);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.0f, 
							 0.0f, 
							 -DEFAULT_SUBARENA_HEIGHT);
		glVertex3f(-DEFAULT_SUBARENA_LENGTH, 
							 0.0f, 
							 -DEFAULT_SUBARENA_HEIGHT);
		glVertex3f(0.0f, 
							 -DEFAULT_SUBARENA_LENGTH, 
							 -DEFAULT_SUBARENA_HEIGHT);
		glVertex3f(-DEFAULT_SUBARENA_LENGTH, 
							 -DEFAULT_SUBARENA_LENGTH, 
							 -DEFAULT_SUBARENA_HEIGHT);
		glVertex3f(0.0f, 
							 -DEFAULT_SUBARENA_LENGTH, 
							 DEFAULT_SUBARENA_HEIGHT);
		glVertex3f(-DEFAULT_SUBARENA_LENGTH, 
							 -DEFAULT_SUBARENA_LENGTH, 
							 DEFAULT_SUBARENA_HEIGHT);
	glEnd();
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

void Arena::setNetworkSubmitFunction(std::function<void (PlayerCommand)> submitNetworkCommandFunc)
{
	this->submitNetworkCommandFunc = submitNetworkCommandFunc;
}

void Arena::executeNetworkPlayerCommand(PlayerCommand command)
{
	 command.execute(&subArenas[SubArena::BOTTOM_ARENA]);

	 // If the command was a drop block, check if we need to clear any layers
	 if (command.getAction() == PlayerCommand::DROP_BLOCK) {
		if (updateLayers(SubArena::BOTTOM_ARENA)) {
			// need to generate a new superblock
			subArenas[TOP_ARENA].newSuperBlock();
			// and send to the other player
			submitNetworkCommandFunc(PlayerCommand::Action::TEST_NEW_BLOCK);
		}

		checkEndCondition();
	 }

	 if (PlayerCommand::Action::I_LOST == command.getAction()) {
		updateWorldStateFunc(GameState::WON);
	 }
}

void Arena::setNetworkPlayerSuperBlockType(SuperBlock::SuperBlockType sbType)
{
	subArenas[SubArena::BOTTOM_ARENA].newSuperBlock(sbType);
}

void Arena::setEndGameFunction(std::function<void (GameState)> updateWorldStateFunc) 
{
	this->updateWorldStateFunc = updateWorldStateFunc;
}
