#include "TextureService.h"
#include "TextureFactory.h"

#define RED_SQUARE_FILENAME "data/redSquareFace.png"
#define BLUE_SQUARE_FILENAME "data/blueSquareFace.png"
#define YELLOW_SQUARE_FILENAME "data/yellowSquareFace.png"
#define GREEN_SQUARE_FILENAME "data/greenSquareFace.png"
#define PURPLE_SQUARE_FILENAME "data/purpleSquareFace.png"

TextureService *TextureService::serviceSingleton = 0;

TextureService::TextureService()
{
	textures[RED_SQUARE_FACE] = TextureFactory::getTextureHandle(RED_SQUARE_FILENAME);
	textures[BLUE_SQUARE_FACE] = TextureFactory::getTextureHandle(BLUE_SQUARE_FILENAME);
	textures[GREEN_SQUARE_FACE] = TextureFactory::getTextureHandle(GREEN_SQUARE_FILENAME);
	textures[PURPLE_SQUARE_FACE] = TextureFactory::getTextureHandle(PURPLE_SQUARE_FILENAME);
	textures[YELLOW_SQUARE_FACE] = TextureFactory::getTextureHandle(YELLOW_SQUARE_FILENAME);	
}

TextureService* TextureService::getTextureServiceInstance() {
	if (!serviceSingleton) { serviceSingleton = new TextureService(); }

	return serviceSingleton;
}

GLuint TextureService::getTexture(Texture texture)
{
	return textures[texture];
}