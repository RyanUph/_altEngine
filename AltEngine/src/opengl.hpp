#ifndef altrender_opengl_api
#define altrender_opengl_api
#include "baseapi.hpp"

#include <glad/glad.h>
#include "exitcodes.hpp"
#include <GLFW/glfw3.h>

class OpenGL : BaseAPI {
	private:
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	}
	void error_callback (int error, const char* desc) {
		std::string text = "Error "+ std::to_string(error) +": "+ std::to_string(desc);
		logger->error((char*)text.c_str());
	}
	GLFWwindow* glfwWindow;
	public:
	void initEngine () {
		glfwSetErrorCallback(error_callback);
		if (!glfwInit()) {
			logger->error((char*)"The engine wasn't able to start. Bye.");
			exit(ExitCodes::ERROR);
		}
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		
		glfwWindow = glfwCreateWindow(width, height, std::to_string(titlename), NULL, NULL);
		if (!glfwWindow) {
			glfwTerminate();
			logger->error((char*)"The engine wasn't able to create a window. Bye.");
			exit(ExitCodes::ERROR);
		}
		glfwSetKeyCallback(glfwWindow, key_callback);
		glfwMakeCurrentContext(glfwWindow);
		gladLoadGL();
		glfwSwapInterval(1);
	}
	void startLoop () {
		while (!glfwWindowShouldClose(glfwWindow)) {
			glfwSwapBuffers(glfwWindow);
			glfwPollEvents();
		}
		logger->log((char*)"Game finished; window should now close... Bye!");
		glfwDestroyWindow(glfwWindow);
		glfwTerminate();
		exit(ExitCodes::SUCCESS);
	}
}
#endif