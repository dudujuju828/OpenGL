
#include "../include/Window.h" // implementing window class
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void framebufferWinCallback(GLFWwindow* window, int width, int height) {
	glViewport(0,0,width,height);
}

bool Window::s_glfw_initialized = false;

void Window::destroy() {
	if (m_window_pointer) { 				 // if window pointer is valid
		glfwDestroyWindow(m_window_pointer); // destroy window object pointer being pointed to
	
		if (s_glfw_initialized) {	
			glfwTerminate();					 // by default terminate glfw
			s_glfw_initialized = false;
		}
	}
}

void Window::setShouldClose(bool truth) {
	glfwSetWindowShouldClose(m_window_pointer,truth);
}

// ensure states are set to default
Window::Window() {
	m_window_pointer = nullptr;
	m_width = -1;
	m_height = -1;
}

Window::~Window() {
	destroy();
}

void Window::create(int width, int height, const char* title) {
	// set private member variables
	m_width = width;
	m_height = height;
	m_title = title;

	// initialize glfw and update global class state
	if (!glfwInit()) {
		s_glfw_initialized = false;
	} else {
		s_glfw_initialized = true;
	}

	// set window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// check valid window creation
	m_window_pointer = glfwCreateWindow(width,height,title,nullptr,nullptr); 
	if (!m_window_pointer) {
		glfwTerminate();
	}
	
	// set opengl context to the window and enable vsync
	glfwMakeContextCurrent(m_window_pointer);   

	glfwSetFramebufferSizeCallback(m_window_pointer,framebufferWinCallback); 	
	
	glfwSwapInterval(1); 					
}

bool Window::shouldClose() const {
	return glfwWindowShouldClose(m_window_pointer);
}

// swap front and back buffers
void Window::swapBuffers() {
	glfwSwapBuffers(m_window_pointer);
}
