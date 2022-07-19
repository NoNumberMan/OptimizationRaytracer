#pragma once
#include "maths.h"

namespace raytracer {
	void add_mesh(const float* vertices, const size_t size);

	void run(byte* pixels, const int width, const int height);
}
