#include <iostream>
#include "opengl.hpp"
#include "keylistener.hpp"
#include "keys.hpp"

/* glm test code */
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
glm::mat4 camera(float Translate, glm::vec2 const & Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}
/* glm test code */

int main() {
	std::string vshader = (char*)"#version 330 core\nlayout (location = 0) in vec4 aPos;\nvoid main() {\n    gl_Position = aPos;\n}\n";
	std::string fshader = (char*)"#version 330 core\nout vec4 FragColor;\nvoid main() {\n    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}\n";
	
	// Let's create a test listener
	KeyListener* listener = new KeyListener();
	// Now, let's create a rendering instance (for testing)
	OpenGL* api = new OpenGL(300, 300, true, (char*)"AltEngine test");
	// Let's init the engine
	api->initEngine();
	
	// Let's compile our shaders now...
	int vertexShader = api->compileVertexGlslShader(vshader);
	int fragmentShader = api->compileFragmentGlslShader(fshader);

    // Now, let's attach them together and start using it!
    api->useShader(api->attachShaders(vertexShader, fragmentShader));
    
    
	// Now, let's render a triangle!
	float points[] = {
		0.0f,  0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f
	};

	// Test glm camera
	auto cam = camera(5.0f, { 0.5f, 0.5f });

	api->renderTriangle(points);
    api->startLoop();

    // Now, let's delete what we don't need anymore
    //api->deleteShader(vertexShader);
    //api->deleteShader(fragmentShader);

	api->deleteShader(vertexShader);
	api->deleteShader(fragmentShader);

	delete api;
	delete listener;
}