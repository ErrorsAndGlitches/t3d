#ifndef RANDOM_ENGINE_H
#define RANDOM_ENGINE_H
/**
 * @file
 * @brief This file provides the RandomEngine factory class
 */

#include <chrono>
#include <random>
#include <limits>

/**
 * @brief RandomEngine class provides an interface to generate 
 * random numbers
 *
 * The class is a singleton class.
 */
class RandomEngine {
	private:
		// random number generation objects
		std::default_random_engine generator;
		std::uniform_int_distribution<int> intDistribution;
		std::uniform_real_distribution<float> realDistribution;

		static RandomEngine *engineInstance;

		/**
		 * @brief Default constructor
		 */
		RandomEngine();

		/**
		 * @brief Deconstructor
		 */
		~RandomEngine();
		
	public:
		/**
		 * @brief Get the singleton RandomEngine instance
		 *
		 * @return A RandomEngine instance
		 */
		static RandomEngine *getRandomEngineInstance();

		/**
		 * @brief Return a random integer in [min, max]
		 *
		 * @param min The minimum integer allowed to return. The default value is
		 * the minimum value permitted by an int integer.
		 * @param max The maximum integer to return. The default value is the
		 * maximum value permitted by an int integer.
		 *
		 * @return A random integer in the interval [min, max]
		 */
		int getRandomInt(int min = (std::numeric_limits<int>::min)(), 
				int max = (std::numeric_limits<int>::max)());

		/**
		 * @brief Return a random float in [min, max]
		 *
		 * @param min The minimum float allowed to return. The default value is
		 * the minimum value permitted by an int float.
		 * @param max The maximum float to return. The default value is the
		 * maximum value permitted by an int float.
		 *
		 * @return A random float in the interval [min, max]
		 */
		float getRandomFloat(float min = (std::numeric_limits<float>::min)(), 
				float max = (std::numeric_limits<float>::max)());
};

#endif
