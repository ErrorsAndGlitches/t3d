#include "SimpleRotation.h"

Vector SimpleRotation::rotate(const Vector& vec, RotationType rotType)
{
	switch (rotType) {
		case RotationType::XCW:
			return Vector(vec.x, -vec.z, vec.y);
		case RotationType::XCCW:
			return Vector(vec.x, vec.z, -vec.y);
		case RotationType::YCW:
			return Vector(vec.z, vec.y, -vec.x);
		case RotationType::YCCW:
			return Vector(-vec.z, vec.y, vec.x);
		case RotationType::ZCW:
			return Vector(-vec.y, vec.x, vec.z);
		case RotationType::ZCCW:
			return Vector(vec.y, -vec.x, vec.z);
	}
}

void SimpleRotation::rotate(Vector& vec, RotationType rotType)
{
	switch (rotType) {
		case RotationType::XCW:
			vec.setPos(vec.x, -vec.z, vec.y);
		case RotationType::XCCW:
			vec.setPos(vec.x, vec.z, -vec.y);
		case RotationType::YCW:
			vec.setPos(vec.z, vec.y, -vec.x);
		case RotationType::YCCW:
			vec.setPos(-vec.z, vec.y, vec.x);
		case RotationType::ZCW:
			vec.setPos(-vec.y, vec.x, vec.z);
		case RotationType::ZCCW:
			vec.setPos(vec.y, -vec.x, vec.z);
	}
}
