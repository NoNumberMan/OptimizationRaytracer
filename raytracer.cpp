#include "raytracer.h"

#include <vector>

namespace raytracer {
	static std::vector<float> _vertices;
	static std::vector<int> _meshes;

	void add_mesh( const float* vertices, const size_t size ) {
		const int start = _vertices.size();
		_vertices.resize(start + size);
		memcpy(_vertices.data() + start, vertices, size);
		_meshes.push_back(start);
	}

	void run( byte* pixels, const int width, const int height ) {
		//our code goes here


		//default screen fill - remove this
		for (int i = 0; i < width * height; ++i) {
			pixels[4 * i + 0] = 255;
			pixels[4 * i + 1] = 0;
			pixels[4 * i + 2] = 255;
			pixels[4 * i + 3] = 255;
		}
	}
}
