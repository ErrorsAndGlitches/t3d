#ifndef TEXTURE_FACTORY_H
#define TEXTURE_FACTORY_H
/**
 * @file
 * @brief This file provides the TextureFactory factory class
 */
#ifdef _WIN32
	#include <windows.h>
	#include <GL/glut.h>
	#include "SDL.h"
	#include "SDL_image.h"
#else
	#include <GL/freeglut.h>
	#include "SDL/SDL.h"
	#include "SDL/SDL_image.h"
#endif


/**
 * @brief TextureFactory class provides an interface to generate OpenGL texture
 * handles
 */
class TextureFactory {
	private:
		/**
		 * @brief Default constructor
		 */
		TextureFactory();

	public:
		/**
		 * @brief Creates an OpenGL texture handle from the input file name
		 *
		 * @param filename File name for an image to open and create a texture map for
		 *
		 * @return An OpenGL texture handle. Returns 0 if the texture map creation
		 * failed
		 */
		static GLuint getTextureHandle(const char *filename);
};

#endif
