#include <iostream>
#include "opengl.hpp"
#include "keylistener.hpp"
#include "keys.hpp"

int main() {
	// Let's create a test listener
	KeyListener* listener = new KeyListener();
	// Now, let's create a rendering instance (for testing)
	OpenGL* api = new OpenGL(300, 300, true, (char*)"AltEngine test");
	// Let's init the engine
	api->initEngine();
	
	// Now, let's render a triangle!
	api->renderTriangle({
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
    });
    
	std::cin.get();
	delete api;
	delete listener;
}