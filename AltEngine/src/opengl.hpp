#ifndef altrender_opengl_api
#define altrender_opengl_api
#include "baseapi.hpp"

#include <glad/glad.h>
#include "exitcodes.hpp"
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
void error_callback (int error, const char* desc) {
	std::string text = "Error "+ std::to_string(error) +":";
	std::cout << (char*)text.c_str() << std::endl;
	std::cout << (char*)desc << std::endl;
}
	
class OpenGL : BaseAPI {
	private:
	bool windowCreated = false;
	GLFWwindow* glfwWindow;
	
	public:
	OpenGL (int width, int height, bool verbose, char* title) : BaseAPI(width, height, verbose, title) {}
	
	void initEngine () {
		glfwSetErrorCallback(error_callback);
		if (!glfwInit()) {
			logger->error((char*)"The engine wasn't able to start. Bye.");
			exit(ExitCodes::ERROR);
		}
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindow = glfwCreateWindow(width, height, titlename, NULL, NULL);
		if (!glfwWindow) {
			glfwTerminate();
			logger->error((char*)"The engine wasn't able to create a window. Bye.");
			exit(ExitCodes::ERROR);
		}
		glfwSetKeyCallback(glfwWindow, key_callback);
		glfwMakeContextCurrent(glfwWindow);
		gladLoadGL();
		glfwSwapInterval(1);
		/* Creating the VAO */
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		
		windowCreated = true;
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
	void renderTriangle (float points[]) {
		if (!windowCreated) {
			return logger->error((char*)"You can't use render before creating a window.");
		}
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
	}
};

#endif