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

		width = 640;
		height = 480;
		
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
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		windowCreated = true;
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
	int compileVertexGlslShader (char* vertSource) {
	    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	    glShaderSource(vertexShader, 1, &vertSource, NULL);
	    glCompileShader(vertexShader);
	    int success;
	    char* log = "";
	    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	    if (!success) {
	    	glGetShaderInfoLog(vertexShader, 512, NULL, log);
	    	logger->error((char*)"I wasn't able to compile the shaders. Error:");
	        logger->error((char*)log);
	        return 1;
	    }
	    return vertexShader;
    }
    int compileFragmentGlslShader (char* source) {
	    int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	    glShaderSource(fragShader, 1, &source, NULL);
	    glCompileShader(fragShader);
	    int success;
		char* log = "";
	    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	    if (!success) {
	    	glGetShaderInfoLog(fragShader, 512, NULL, log);
	    	logger->error("I wasn't able to compile the shaders. Error:");
	        logger->error(log);
	        return 1;
	    }
	    return fragShader;
    }
    int attachShaders (int vertex, int fragment) {
    	int program = glCreateProgram();
    	glAttachShader(program, vertex);
    	glAttachShader(program, fragment);
    	glLinkProgram(program);
    	
    	return program;
    }
    void deleteShader (int shader) {
    	glDeleteShader(shader);
    }
    void useShader (int program) {
    	glUseProgram(program);
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
};

#endif