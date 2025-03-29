
#pragma once

#include <string>

class Renderer {
public:
	Renderer();
	~Renderer();
	
	bool init(int screenWidth, int screenHeight);

	void clear();
	
	void drawRect(float x, float y, float width, float height);

	void shutdown();

private:
	unsigned int m_shaderProgram;

	unsigned int m_quadVAO;
	unsigned int m_quadVBO;
	unsigned int m_quadEBO;

	int m_screenWidth;
	int m_screenHeight;
};
