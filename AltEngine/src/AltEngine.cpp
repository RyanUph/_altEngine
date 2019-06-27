#include <iostream>
#include "opengl.hpp"
#include "keylistener.hpp"
#include "keys.hpp"

int main() {
	char* vshader = (char*)"#version 330 core\nlayout (location = 0) in vec3 aPos;\nvoid main() {\n    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}";
	char* fshader = (char*)"#version 330 core\nout vec4 FragColor;\nvoid main() {\n    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n";
	
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
    
    // Now, let's delete what we don't need anymore
    api->deleteShader(vertexShader);
    api->deleteShader(fragmentShader);
    
	// Now, let's render a triangle!
	float points[] = {
		0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
	};

	api->renderTriangle(points);
    api->startLoop();
    
	std::cin.get();
	delete api;
	delete listener;
}