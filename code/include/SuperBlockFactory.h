#ifndef SUPERBLOCK_FACTORY_H
#define SUPERBLOCK_FACTORY_H
/**
 * @file
 * @brief This file provides the SuperBlockFactory factory class
 */

#include <chrono>
#include <random>
#include "SuperBlock.h"

/**
 * @brief SuperBlockFactory class provides an interface to generate 
 * SuperBlocks in a random manner
 *
 * The class is a singleton class used to generate SuperBlocks in a 
 * pseudo random manner
 */
class SuperBlockFactory {
	private:
		/**
		 * @brief Default constructor
		 */
		SuperBlockFactory();
		
		/*
		 * Single instance of the SuperBlockFactory
		 */
		static SuperBlockFactory *factorySingleton;

		// random number generation objects
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution;

	public:
		/**
		 * @brief Get an instance of the SuperBlockFactory class
		 *
		 * Do not call delete() on the instance returned by the method. The singleton
		 * is shared among its users.
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
