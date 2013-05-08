#ifndef SUPERBLOCK_FACTORY_H
#define SUPERBLOCK_FACTORY_H
/**
 * @file
 * @brief This file provides the SuperBlockFactory factory class
 */

#include "SuperBlock.h"
#include "RandomEngine.h"

/**
 * @brief SuperBlockFactory class provides an interface to generate 
 * SuperBlocks in a random manner
 *
 * The class is a singleton class used to generate SuperBlocks in a 
 * pseudo random manner
 */
class SuperBlockFactory {
	private:
		// random engine to produce random numbers corresponding to a SuperBlock
		// type
		RandomEngine *randEng;

		/**
		 * @brief Default constructor
		 */
		SuperBlockFactory();

		/**
		 * @brief Deconstructor
		 *
		 * The deconstructor is private so that users cannot delete the singleton
		 * instance
		 */
		~SuperBlockFactory();
		
		/*
		 * Single instance of the SuperBlockFactory
		 */
		static SuperBlockFactory *factorySingleton;

	public:
		/**
		 * @brief Get an instance of the SuperBlockFactory class
		 *
		 * @return An instance of the SuperBlockFactory class
		 */
		static SuperBlockFactory* getSuperBlockFactoryInstance();

		/**
		 * @brief Create and return a SuperBlock of the given type. If no type is
		 * given, then a random SuperBlockType is returned.
		 *
		 * @param blockType A SuperBlockType to return
		 *
		 * @return A SuperBlock
		 */
		SuperBlock* getSuperBlock(SuperBlock::SuperBlockType blockType
				= (SuperBlock::SuperBlockType) 
				RandomEngine::getRandomEngineInstance()->getRandomInt(
					0, 
					SuperBlock::NUM_SUPER_BLOCK_TYPES - 1));
};

#endif
