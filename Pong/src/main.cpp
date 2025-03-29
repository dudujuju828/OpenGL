#include <iostream>

#include "../include/Window.h"
#include "../include/Input.h"
#include "../include/Renderer.h"
#include "../include/Game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {

	Window window;
	Input input;
	if (!window.create(800,600,"Pong")) {
		std::cerr << "Window creation error.\n";
		return -1;
	}
	
	Renderer renderer;
	renderer.init(800,600);

	Game game;
	game.init(800,600);
	
	float lastTime = static_cast<float>(glfwGetTime());
	
	while (!window.shouldClose()) {
		input.pollEvents(window);

	    float currentTime = static_cast<float>(glfwGetTime());
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        game.update(input, dt);

		renderer.clear();
		game.render(renderer);
		window.swapBuffers();
	}
    renderer.shutdown();
    return 0;
}
