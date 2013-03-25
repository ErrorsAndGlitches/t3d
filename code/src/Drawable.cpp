#include "Drawable.h"

const float Drawable::WHITE[3] = { 1.0f, 1.0f, 1.0f };
const float Drawable::BLACK[3] = { 0.0f, 0.0f, 0.0f };
const float *const Drawable::DEFAULT_COLOR = BLACK;

void Drawable::draw() const
{
	draw(DEFAULT_COLOR);
}
