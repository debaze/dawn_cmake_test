#include <iostream>
#include "GLFW/glfw3.h"

const uint32_t WINDOW_WIDTH	= 512;
const uint32_t WINDOW_HEIGHT = 256;
const char* WINDOW_TITLE = "Title";

int main() {
	if (!glfwInit()) return 1;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
}