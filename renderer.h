#pragma once
#include "maths.h"

namespace raytracer {
	void init_screen(const int width, const int height);
	void terminate_screen();
	void draw_screen(const byte* pixels);
}