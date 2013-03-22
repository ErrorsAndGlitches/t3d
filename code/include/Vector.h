#ifndef VECTOR_H
#define VECTOR_H
/**
 * @brief Contains the Vector structure declaration.
 * @author Benjamyn
 *
 * All vectors have their tail implicitly start at the origin and the head at
 * the internal (x, y, z) position
 */

/**
 * @brief A simple 3D vector structure
 */
typedef struct Vector {
	public:
		float x, y, z;

		/**
		 * @brief Default constructor, sets the end point of the vector
		 */
		Vector(): x(), y(), z() {}

		/**
		 * @brief Constructor to set the starting position
		 *
		 * @param x X starting coordinate
		 * @param y Y starting coordinate
		 * @param z Z starting coordinate
		 */
		Vector(float x, float y, float z): x(x), y(y), z(z) {}

		/**
		 * @brief The parameter and current vector are added together. The
		 * resulting vector is assigned to the current vector.
		 *
		 * @param v Vector to add to the current vector
		 */
		void operator+=(const Vector& v) { x += v.x; y += v.y; }

		/**
		 * @brief The parameter vector is subtracted from the current vector. The
		 * resulting vector is assigned to the current vector.
		 *
		 * @param v Vector to subtract from the current vector
		 */
		void operator-=(const Vector& v) { x -= v.x; y -= v.y; }

		/**
		 * @brief Assignment operator.
		 *
		 * @param v Vector to assign to the current vector
		 */
		void operator=(const Vector& v) { x = v.x; y = v.y; }

		/**
		 * @brief Adds the current and parameter vector, returning the new vector,
		 * which is an xvalue
		 *
		 * @param v Vector to add to the current vector
		 *
		 * @return An xvalue to the new vector
		 */
		Vector operator+(const Vector& v) const { return Vector(x + v.x, y + v.y, z + v.z); }

		/**
		 * @brief Update the relative position of the head of the vector
		 *
		 * @param xx Delta x
		 * @param yy Delta y
		 * @param zz Delta z
		 */
		void updateRelaPos(float xx, float yy, float zz) { x += xx; y += yy; z += zz; }
} Vector;

#endif
