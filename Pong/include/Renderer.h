
#pragma once

#include <string>

#include "Window.h"
#include "Texture.h"

class Renderer {
public:
	Renderer();
	~Renderer();
	
	bool init(const Window &window);

	void clear();
	
	void drawRect(float x, float y, float width, float height);
	void drawBackdrop(float x, float y, float width, float height);
	void useProgram(unsigned int programID);
	void setFramebufferVec3(const char * uniformName, float r, float g, float b);
	void setFramebufferFloat(const char * uniformName, float value);
	void setDefaultbufferFloat(const char * uniformName, float value);
	
	unsigned int getFramebufferProgram() { return m_frameBufferProgram; }
	unsigned int getDefaultbufferProgram() { return m_defaultBufferProgram; }
	
	void postProcess(float x, float y, float width, float height, Window &window);

	void shutdown();

private:

	unsigned int m_frameBufferProgram;
	unsigned int m_defaultBufferProgram;	

	unsigned int m_frameBufferObject;
	unsigned int m_frameBufferTexture;

	unsigned int m_quadVAO;
	unsigned int m_quadVBO;
	unsigned int m_quadEBO;

	unsigned int m_screenWidth;
	unsigned int m_screenHeight;

	Texture m_backdropTexture;
};
