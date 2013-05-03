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
		 * @brief Creates and returns an random SuperBlock
		 *
		 * It is up to the user to delete() the SuperBlock object.
		 *
		 * @return A random SuperBlock
		 */
		SuperBlock* getRandomSuperBlock();
};

#endif
