#ifndef PLATFORM_H
#define PLATFORM_H
/**
 * @file
 * @brief Contains the Platform class declaration.
 * @author Zach
 */

#include <iostream> 

#include <GL/glut.h>                    // GLUT
#include <GL/glu.h>                     // GLU
#include <GL/gl.h>                      // OpenGL



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
	Platform(int dimension = 4) {this->dimension = dimension;}
	
	/**
	* @brief Draw the platform
	*/
	void draw();

	~Platform(void){}

private:
	int dimension;	//How many blocks will be in each row and col
	
};

#endif