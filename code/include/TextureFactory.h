#ifndef TEXTURE_FACTORY_H
#define TEXTURE_FACTORY_H
/**
 * @file
 * @brief This file provides the TextureFactory factory class
 */

#include <GL/freeglut.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

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
