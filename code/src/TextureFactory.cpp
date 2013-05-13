#include "TextureFactory.h"

TextureFactory::TextureFactory()
{ }

/**
 * @brief Load a texture, returning the OpenGL texture handle
 *
 * @param filename Filename of image
 *
 * @return OpenGL texture handle
 */
GLuint TextureFactory::getTextureHandle(const char *filename)
{
	SDL_Surface *surface;
	GLuint textureid;
	int mode;
	
	surface = IMG_Load(filename);
	
	// could not load filename
	if (!surface)
		return 0;
	
	// work out what format to tell glTexImage2D to use...
	if (surface->format->BytesPerPixel == 3) // RGB 24bit
		mode = GL_RGB;
	else if (surface->format->BytesPerPixel == 4) // RGBA 32bit
		mode = GL_RGBA;
	else {
		SDL_FreeSurface(surface);
		return 0;
	}
	
	// create one texture name
	glGenTextures(1, &textureid);
	
	// tell opengl to use the generated texture name
	glBindTexture(GL_TEXTURE_2D, textureid);
	
	// build 2d mip map
  gluBuild2DMipmaps(GL_TEXTURE_2D,     // texture to specify
                    mode,              // internal texture storage format
                    surface->w,        // texture width
                    surface->h,        // texture height
                    mode,              // pixel format
                    GL_UNSIGNED_BYTE,	 // color component format
                    surface->pixels);  // pointer to texture image
	
	// these affect how this texture is drawn later on...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// have the texture replace the color of the object being drawn
	glActiveTexture(textureid);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// clean up
	SDL_FreeSurface(surface);
	
	return textureid;
}
