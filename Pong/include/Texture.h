
#pragma once

#include <GLFW/glfw3.h>

class Texture {
	unsigned int m_textureID;

public:
	void init(const char* texturePath);
	void bind(GLenum target);
};
