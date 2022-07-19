#include "stdio.h"
#include <cstdlib>

#define GLEW_STATIC
#include "measurements.h"
#include "raytracer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "renderer.h"


#define WIDTH_INIT 1280
#define HEIGHT_INIT 720


namespace raytracer {
	typedef struct raytracer_data_t {
		int width;
		int height;
		byte* pixels;
	} raytracer_data;

	static void on_framebuffer_resize(GLFWwindow* window, const int width, const int height) {
		raytracer_data* data = (raytracer_data*) glfwGetWindowUserPointer(window);

		data->width = width;
		data->height = height;
		free(data->pixels);
		data->pixels = (byte*) calloc(width * height * 4, 1);
		
		//reset screen
		terminate_screen();
		init_screen(width, height);
		glViewport(0, 0, width, height);
	}
}


int main() {
	glfwInit();

	glfwDefaultWindowHints();
	GLFWwindow* window = glfwCreateWindow(WIDTH_INIT, HEIGHT_INIT, "RayTracer", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, raytracer::on_framebuffer_resize);
	glewInit();
	glfwShowWindow(window);

	raytracer::init_screen(WIDTH_INIT, HEIGHT_INIT);

	raytracer::raytracer_data data;
	data.width = WIDTH_INIT;
	data.height = HEIGHT_INIT;
	data.pixels = (byte*) calloc(WIDTH_INIT * HEIGHT_INIT * 4, 1);
	glfwSetWindowUserPointer(window, &data);

	while (!glfwWindowShouldClose(window)) {
		raytracer::scoped_timer t([](const int dt) { printf("frame took %d ms - %d fps\n", dt, 1000 / dt); });
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		raytracer::run(data.pixels, data.width, data.height);
		raytracer::draw_screen(data.pixels);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}