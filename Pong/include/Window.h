
#pragma once

struct GLFWwindow; // forward declaration

#include <string>

class Window {
private:
	void destroy();	// function for destructor to call

	GLFWwindow* m_window_pointer; // store window pointer	
	int m_width;  				  // store window width
	int m_height;                 // store window height 
	std::string m_title;

	static bool s_glfw_initialized;	// global glfw state

public:
	Window();
	~Window(); // object lifetime will be hidden from client

	void create(int width, int height, const char* title);	// initialize glfw and create window

	bool shouldClose() const; // query whether window should close
	void setShouldClose(bool trut);

	void swapBuffers(); // swap front and back buffers
	float getTime();

	int getWidth() const { return m_width; }   // implicitly inline, returns window width
	int getHeight() const { return m_height; } // returns window height
	
	GLFWwindow* getNativePointer() const { return m_window_pointer; }
};

