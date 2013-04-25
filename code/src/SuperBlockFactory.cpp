#include "SuperBlockFactory.h"
#include <iostream>

// initialize to NULL
SuperBlockFactory *SuperBlockFactory::factorySingleton = 0;

SuperBlockFactory::SuperBlockFactory(): 
	generator(std::chrono::system_clock::now().time_since_epoch().count()),
	distribution(0, SuperBlock::NUM_SUPER_BLOCK_TYPES - 1)
{ }

SuperBlockFactory* SuperBlockFactory::getSuperBlockFactoryInstance() {
	if (!factorySingleton) {
		factorySingleton = new SuperBlockFactory();
	}
	
	return factorySingleton;
}

SuperBlock* SuperBlockFactory::getRandomSuperBlock() {
	return new SuperBlock((SuperBlock::SuperBlockType) distribution(generator));
}
