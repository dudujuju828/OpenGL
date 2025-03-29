
#include "../include/Input.h"
#include <algorithm>

#include <GLFW/glfw3.h>

Input::~Input() {

}

Input::Input() {
	m_key_map[Key::W] = false;	
	m_key_map[Key::A] = false;	
	m_key_map[Key::S] = false;	
	m_key_map[Key::D] = false;	
	m_key_map[Key::Up] = false;	
	m_key_map[Key::Down] = false;	
	m_key_map[Key::Left] = false;	
	m_key_map[Key::Right] = false;	
}

void Input::pollEvents(const Window &window) {

	glfwPollEvents();
	
	for (auto& pair : m_key_map) {
		Key key = pair.first;	
	
		int glfwKeyCode = 0;

		switch (key) {
			case Key::W : glfwKeyCode = GLFW_KEY_W; break;
			case Key::A : glfwKeyCode = GLFW_KEY_A; break;
			case Key::S : glfwKeyCode = GLFW_KEY_S; break;
			case Key::D : glfwKeyCode = GLFW_KEY_D; break;
			case Key::Up : glfwKeyCode = GLFW_KEY_UP; break;
			case Key::Down : glfwKeyCode = GLFW_KEY_DOWN; break;
			case Key::Left : glfwKeyCode = GLFW_KEY_LEFT; break;
			case Key::Right : glfwKeyCode = GLFW_KEY_RIGHT; break;
		}
	
		if (glfwKeyCode != 0) {
			int state = glfwGetKey(window.getNativePointer(),glfwKeyCode);
			pair.second = (state == GLFW_PRESS || state == GLFW_REPEAT);	
		}
	}
}

bool Input::isPressed(Key key) const {
	auto it = m_key_map.find(key);	
	if (it != m_key_map.end()) {
		return it->second;
	}
	return false;
}
