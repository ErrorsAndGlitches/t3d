#ifndef PLATFORM_H
#define PLATFORM_H
/**
 * @file
 * @brief Contains the Platform class declaration.
 * @author Zach
 */

#include <iostream> 

#ifdef _WIN32
	#include <windows.h>
#endif

#include <GL/glut.h>                    // GLUT
#include <GL/glu.h>                     // GLU
#include <GL/gl.h>                      // OpenGL

#include "Defs.h"



/**
 * @brief A plateform is an n*n grid which acts as the landing site for blocks.
 */
class Platform
{
public:

	/**
	* @brief Constructs an n*n plateform of the given dimension. 
	*
	* @param dimension The dimension of the plateform.
	*/
	Platform(int dimension = DEFAULT_SUBARENA_LENGTH) {this->dimension = dimension;}
	
	/**
	* @brief Draw the platform
	*/
	void draw();

	~Platform(void){}

private:
	int dimension;	//How many blocks will be in each row and col
	
};

#endif