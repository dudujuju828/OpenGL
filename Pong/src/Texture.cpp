
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../include/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#include <iostream>

void Texture::init(const char* texturePath) {

	int width;
	int height;
	int nrChannels;

	unsigned char* image_data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (!image_data) {
		std::cerr << "Error loading image data from path :" << texturePath << "\n";
	}
	
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	m_textureID = textureID;

	GLenum format = 0;
	if (nrChannels == 1) {
		format = GL_RED;
	} else if (nrChannels == 3) {
		format = GL_RGB;
	} else if (nrChannels == 4) {
		format = GL_RGBA;
	} else {
		std::cerr << "Incompatible channel count\n";
	}
	
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image_data);	
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glGenerateMipmap(GL_TEXTURE_2D);
	
}

void Texture::bind(GLenum target) {
	glActiveTexture(target);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}
