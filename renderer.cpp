#include "renderer.h"

#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>

namespace raytracer {

	static const char* vertexShaderSource = R"(
		#version 330
		layout(location=0) in vec2 vertices; 
		layout(location=1) in vec2 uvs;

		out vec2 fragUvs;

		void main() {
			fragUvs = uvs;
			gl_Position = vec4(vertices.x, vertices.y, 0.0f, 1.0f);
		}
	)";

	static const char* fragmentShaderSource = R"(
		#version 330

		in vec2 fragUvs;
		out vec4 color;

		uniform sampler2D tex;

		void main() {
			color = texture(tex, fragUvs);
		}
	)";


	static GLuint _textureId = -1;
	static GLuint _programId = -1;
	static GLuint _screenBuffer = -1;
	static int _width = -1;
	static int _height = -1;

	void init_screen(const int width, const int height) {
		_width = width;
		_height = height;

		glGenTextures(1, &_textureId);

		glBindTexture(GL_TEXTURE_2D, _textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		const GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		const GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		_programId = glCreateProgram();

		glShaderSource(vs, 1, &vertexShaderSource, 0);
		glShaderSource(fs, 1, &fragmentShaderSource, 0);
		glCompileShader(vs);
		glCompileShader(fs);
		glAttachShader(_programId, vs);
		glAttachShader(_programId, fs);
		glLinkProgram(_programId);
		glDetachShader(_programId, vs);
		glDetachShader(_programId, fs);
		glDeleteShader(vs);
		glDeleteShader(fs);
		glUseProgram(_programId);

		//vertex + uv coordinates
		constexpr float data[24] = {
			-1.0f, -1.0f, 0.0f, 0.0f,
			-1.0f, +1.0f, 0.0f, 1.0f,
			+1.0f, -1.0f, 1.0f, 0.0f,
			+1.0f, -1.0f, 1.0f, 0.0f,
			-1.0f, +1.0f, 0.0f, 1.0f,
			+1.0f, +1.0f, 1.0f, 1.0f
		};

		glGenBuffers(1, &_screenBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _screenBuffer);
		glBufferData(GL_ARRAY_BUFFER, 96, data, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)(0 * sizeof(float)));
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}

	void terminate_screen() {
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &_textureId);

		glUseProgram(0);
		glDeleteProgram(_programId);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &_screenBuffer);
	}

	void draw_screen(const byte* pixels) {
		glBindTexture(GL_TEXTURE_2D, _textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glUseProgram(_programId);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
