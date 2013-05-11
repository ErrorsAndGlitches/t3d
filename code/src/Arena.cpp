#include <iostream>
#include "Arena.h"
#include "Player.h"
#include "Defs.h"


Arena::Arena(void): GameObject()
{ }


void Arena::assignToArena(Player *player, SubArena subarena)
{
	playerArenaMap.insert ( std::pair<SubArena,int>(subarena, player->getID()));
	player->setArena(this);
}

void Arena::submitCommand(Player *player, PlayerCommand command)
{
	std::map<SubArena, int>::iterator it;
	for (it = playerArenaMap.begin(); it != playerArenaMap.end(); it++) {
		if ((*it).second == player->getID()) {
		   SubArena subarena = (*it).first;
		   command.execute(&subArenas[subarena]);
	   }
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

void Arena::drawPlateform() const
{
	float thinkness = .01;	//How think the plateform will be
	float color = 0;
	int dimension = DEFAULT_SUBARENA_LENGTH;
	float step = 1.0 / (dimension * dimension * 3);	//colloring pattern offsets

	glPushMatrix();
		glScalef(1, 1, thinkness);

		//Tile grid
		for (int row = 0; row < dimension; row++) {
			for (int col = 0; col < dimension; col++) {
				float colorR = color;  color+= step;
				float colorG = color;  color+= step;
				float colorB = color;  color+= step;

				glPushMatrix();
					glColor3f(colorR, colorG, colorB);
					glTranslatef(row + .5, col + .5, 0);
					glutSolidCube(1);
				glPopMatrix();
			}
		}
	glPopMatrix();
}
