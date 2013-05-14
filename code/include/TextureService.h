#ifndef TEXTURE_SERVICE_H
#define TEXTURE_SERVICE_H
/**
 * @file
 * @brief This file provides the TextureService service class
 */
#ifdef _WIN32
	#include <windows.h>
	#include <GL/glut.h>
#else
	#include <GL/freeglut.h>
#endif


/**
 * @brief TextureService class provides an interface to initialize and retrieve OpenGL texture
 * handles
 *
 * The class is a singleton class used to generate SuperBlocks in a 
 * pseudo random manner
 */
class TextureService {
	public:

		/** 
		 * @brief The available textures
		 *
		 */
		enum Texture {
			PURPLE_SQUARE_FACE, 
			RED_SQUARE_FACE, 
			YELLOW_SQUARE_FACE, 
			BLUE_SQUARE_FACE, 
			GREEN_SQUARE_FACE,
			GREY_SQUARE_FACE,
			BACKGROUND,
			TEXTURE_COUNT
		};

		/** 
		 * @brief Get an instance of the TextureService class
		 *
		 * @return An instance of the TextureService class
		 */
		static TextureService* getTextureServiceInstance();


		/**
		 * @brief gets an OpenGL texture handle for the given texture
		 *
		 * @param filename File name for an image to open and create a texture map for
		 *
		 * @return An OpenGL texture handle. Returns 0 if the texture map creation
		 * failed
		 */
		 GLuint getTexture(Texture texture);

	private:
		/**
		 * @brief Default constructor
		 */
		TextureService();

		/**
		 * @brief Deconstructor
		 *
		 * The deconstructor is private so that users cannot delete the singleton
		 * instance
		 */
		~TextureService(){}

		/*
		 * Single instance of the TextureService
		 */
		static TextureService *serviceSingleton;

		//List of texture IDs
		GLuint textures[TEXTURE_COUNT];
};

#endif
