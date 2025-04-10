
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>
#include <chrono>

#include "../include/Window.h"
#include "../include/Input.h"
#include "../include/Renderer.h"
#include "../include/Game.h"
#include "../include/AudioEngine.h"

float processDeltaTime(float &last_time) {
	float current_time = static_cast<float>(glfwGetTime());
    float dt = current_time - last_time;
    last_time = current_time;

	return dt;
}

int main() {

	// Default values
	Window window;
	Input input;
	Renderer renderer;
	Game game;

	// Initialization
	window.create(1920,1080,"Pong");
	renderer.init(window);
	game.init(window);
	
	// Delta time
	float last_time = static_cast<float>(glfwGetTime());

	while (!window.shouldClose())
	{
		float dt = processDeltaTime(last_time);

		game.render(renderer, window, input, dt);
	}

    return 0;
}
