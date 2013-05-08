#include "SuperBlockFactory.h"

SuperBlockFactory *SuperBlockFactory::factorySingleton = NULL;

SuperBlockFactory::SuperBlockFactory():
	randEng(RandomEngine::getRandomEngineInstance())
{ }

SuperBlockFactory::~SuperBlockFactory()
{ }

SuperBlockFactory* SuperBlockFactory::getSuperBlockFactoryInstance() {
	if (!factorySingleton) { factorySingleton = new SuperBlockFactory(); }

	return factorySingleton;
}

SuperBlock* SuperBlockFactory::getSuperBlock(SuperBlock::SuperBlockType blockType)
{
	return new SuperBlock(blockType);
}
