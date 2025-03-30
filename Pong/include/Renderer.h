
#pragma once

#include <string>

#include "Window.h"

class Renderer {
public:
	Renderer();
	~Renderer();
	
	bool init(const Window &window);

	void clear();
	
	void drawRect(float x, float y, float width, float height);

	void shutdown();

private:

	unsigned int m_shaderProgram;

	unsigned int m_quadVAO;
	unsigned int m_quadVBO;
	unsigned int m_quadEBO;

	unsigned int m_screenWidth;
	unsigned int m_screenHeight;
};
