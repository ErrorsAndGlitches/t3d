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

SuperBlock* SuperBlockFactory::getRandomSuperBlock() {
	return new SuperBlock((SuperBlock::SuperBlockType) 
				randEng->getRandomInt(0, SuperBlock::NUM_SUPER_BLOCK_TYPES - 1));
}
