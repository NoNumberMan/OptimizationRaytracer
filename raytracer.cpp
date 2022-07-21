#include "raytracer.h"

#include <vector>

namespace raytracer {
	static std::vector<float> _vertices;
	static std::vector<int> _meshes;


	typedef struct ray_t {
		vec3f pos;
		vec3f dir;
		float t;
	} ray;

	static void triangle_ray_intersection( ray& ray, const int triangleIdx ) {
		const vec3f v0(_vertices[9 * triangleIdx + 0], _vertices[9 * triangleIdx + 1], _vertices[9 * triangleIdx + 2]);
		const vec3f v1(_vertices[9 * triangleIdx + 3], _vertices[9 * triangleIdx + 4], _vertices[9 * triangleIdx + 5]);
		const vec3f v2(_vertices[9 * triangleIdx + 6], _vertices[9 * triangleIdx + 7], _vertices[9 * triangleIdx + 8]);

		const vec3f edge1 = v1 - v0;
		const vec3f edge2 = v2 - v0;
		const vec3f h = ray.dir.cross(edge2);
		const float a = h.dot(edge1);
		if (a > -0.0001f && a < 0.0001f) return;

		const float f = 1.0f / a;
		const vec3f s = ray.pos - v0;
		const float u = f * s.dot(h);
		if (u < 0.0f || u > 1.0f) return;

		const vec3f q = s.cross(edge1);
		const float v = f * ray.dir.dot(q);
		if (v < 0.0f || u + v > 1.0f) return;

		const float t = f * edge2.dot(q);
		if (t > 0.0001f) ray.t = std::min(ray.t, t);
	}


	void add_mesh( const float* vertices, const size_t size ) {
		const int start = _vertices.size();
		_vertices.resize(start + size);
		memcpy(_vertices.data() + start, vertices, size * sizeof(float));
		_meshes.push_back(start);
	}

	static float t = 0.0f;
	void run( byte* pixels, const int width, const int height ) {
		//our code goes here
		memset(pixels, 0, 4 * width * height);

		const float ratio = (float) width / (float) height;

		const vec3f camPos(0.0f, 0.0f, -16.0f);
		const vec3f camDir = vec3f(0.1f * std::cos(t), 0.1f * std::sin(t), 1.0f).normalized();
		const vec3f up(0.0f, 1.0f, 0.0f);
		const vec3f camx = up.cross(camDir);
		const vec3f camy = camx.cross(camDir);

		const vec3f topLeft = camPos + 2.0f * camDir - 0.5f * camx + 0.5f / ratio * camy;

		for (int x = 0; x < width; ++x) {
			for (int y = 0; y < height; ++y) {
				const vec3f pixelPos = topLeft + 1.0f * x * camx / width - 1.0f / ratio * y * camy / height;

				ray ray;
				ray.pos = camPos;
				ray.dir = (pixelPos - camPos).normalized();
				ray.t = 1e30f;

				for (int i = 0; i < _vertices.size() / 9; ++i) {
					triangle_ray_intersection(ray, i);
				}

				if ( ray.t < 1e30f ) {
					const int idx = x + width * y;
					pixels[4 * idx + 0] = 255;
					pixels[4 * idx + 1] = 0;
					pixels[4 * idx + 2] = 255;
					pixels[4 * idx + 3] = 255;
				}
			}
		}

		t += 0.02f;
	}
}
