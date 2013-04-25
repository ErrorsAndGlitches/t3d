#ifndef SIMPLE_ROTATION_H
#define SIMPLE_ROTATION_H
/**
 * @file
 * @brief Contains the SimpleRotation class declaration.
 * @author Benjamyn
 */

#include "Vector.h"

/**
 * @brief A SimpleRotation is a simple class that computes 90 degree rotations
 * in three dimensional space about the fundamental axes. This class is only
 * performs calculations on Vector structs.
 *
 * All the operations are performed through static methods in the class. Objects
 * of this class cannot be constructed.
 */
class SimpleRotation {
	private:
		/**
		 * @brief Hide the constructor
		 */
		SimpleRotation();

	public:
		/**
		 * @brief Rotation type that can be performed by SimpleRotation
		 */
		typedef enum { XCW, XCCW, YCW, YCCW, ZCW, ZCCW, NUM_ROTATION_TYPES} RotationType;

		/**
		 * @brief Perform a 90 degree rotation on the given input vector and return
		 * the resulting vector
		 *
		 * @param vec Vector to rotate
		 * @param rotType Rotation type
		 *
		 * @return The rotated vector
		 */
		static Vector rotate(const Vector& vec, RotationType rotType);

		/**
		 * @brief This method performs the same operations as the other rotate method
		 * except a new Vector is not created. The input vector is updated to 
		 * reflect the rotation operation i.e. it is rotated.
		 *
		 * @param vec Input vector to rotate
		 * @param rotType Rotation type
		 */
		static void rotate(Vector& vec, RotationType rotType);
};

#endif
