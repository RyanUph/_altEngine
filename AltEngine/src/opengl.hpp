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
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(points), points, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	}
	static unsigned int compileVertexGlslShader (const std::string& vertSource) {
	    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* src = vertSource.c_str();
	    glShaderSource(vertexShader, 1, &src, nullptr);
	    glCompileShader(vertexShader);
	    int success;
	    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	    if (!success) {
			int length;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
			char* log = (char*)alloca(length * sizeof(char));
	    	glGetShaderInfoLog(vertexShader, length, &length, log);
			AltLogger* logger = new AltLogger(true);
			logger->error((char*)"Vertex shader compilation failed. Error:");
	        logger->error((char*)log);
	        return 1;
	    }
	    return vertexShader;
    }
    static unsigned int compileFragmentGlslShader (const std::string& fragSource) {
	    int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* src = fragSource.c_str();
	    glShaderSource(fragShader, 1, &src, nullptr);
	    glCompileShader(fragShader);
	    int success;
		char* log;
	    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	    if (!success) {
			int length;
			glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &length);
			char* log = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(fragShader, length, &length, log);
			AltLogger* logger = new AltLogger(true);
			logger->error((char*)"Fragment shader compilation failed. Error:");
			logger->error((char*)log);
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
    	glDeleteProgram(shader);
    }
    void useShader (int program) {
    	glUseProgram(program);
    }
	void startLoop () {
		while (!glfwWindowShouldClose(glfwWindow)) {
			glClear(GL_COLOR_BUFFER_BIT);
			glDrawArrays(GL_TRIANGLES, 0, 3);
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