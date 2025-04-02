#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../include/Renderer.h"
#include "../include/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

bool Renderer::init(const Window &window) {
	m_screenWidth = window.getWidth();
	m_screenHeight = window.getHeight();
	
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	
	glEnable(GL_BLEND);
	
	m_backdropTexture.init("./images/stone-wall-texture.jpg");
	m_backdropTexture.bind(GL_TEXTURE0);
	
	Shader framebuffer_program("./shaders/framebuffer_vertex.glsl", "./shaders/framebuffer_fragment.glsl");
	m_frameBufferProgram = framebuffer_program.getProgramID();
	
	Shader defaultbuffer_program("./shaders/defaultbuffer_vertex.glsl", "./shaders/defaultbuffer_fragment.glsl");
	m_defaultBufferProgram = defaultbuffer_program.getProgramID();
	
	float vertices[] = { 
		0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	
	glGenVertexArrays(1, &m_quadVAO);
	glGenBuffers(1, &m_quadVBO);
	glGenBuffers(1, &m_quadEBO);

	glBindVertexArray(m_quadVAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_quadEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
	
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	
	unsigned int textureColorBuffer;
	glGenTextures(1, &textureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_screenWidth, m_screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "Error with framebuffer completion.\n";
	}
	
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);

	m_frameBufferObject = framebuffer;
	m_frameBufferTexture = textureColorBuffer;

	glBindVertexArray(0);
	
	return true;
}

void Renderer::useProgram(unsigned int programID) {
	glUseProgram(programID);
}

void Renderer::setFramebufferVec3(const char* uniformName, float r, float g, float b) {
	GLint Location = glGetUniformLocation(m_frameBufferProgram, uniformName);
	glUniform3f(Location, r, g, b);
}

void Renderer::setDefaultbufferFloat(const char* uniformName, float value) {
	GLint Location = glGetUniformLocation(m_defaultBufferProgram, uniformName);
	glUniform1f(Location, value);
}

void Renderer::setFramebufferFloat(const char* uniformName, float value) {
	GLint Location = glGetUniformLocation(m_frameBufferProgram, uniformName);
	glUniform1f(Location, value);
}

void Renderer::clear() {
	glClearColor(0.2f,0.2f,0.2f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawBackdrop(float x, float y, float width, float height) {
	
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_frameBufferObject);
	m_backdropTexture.bind(GL_TEXTURE0);

	int samplerLocation = glGetUniformLocation(m_frameBufferProgram, "gSampler");
	glUniform1i(samplerLocation, 0);
	
	int textureOnLocation = glGetUniformLocation(m_frameBufferProgram, "textureOn");
	glUniform1i(textureOnLocation, 1);
	
	glm::mat4 projection = glm::ortho(0.0f, (float)m_screenWidth, (float)m_screenHeight, 0.0f, -1.0f, 1.0f);	

	glm::mat4 model(1.0f);
	
	model = glm::translate(model, glm::vec3(x,y,0.0f));
	model = glm::scale(model, glm::vec3(width, height, 1.0f));

	GLint projLoc = glGetUniformLocation(m_frameBufferProgram, "u_projection");
	GLint modelLoc = glGetUniformLocation(m_frameBufferProgram, "u_model");
	
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(m_quadVAO);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glUniform1i(textureOnLocation, 0);
	glBindVertexArray(0);
}


void Renderer::drawRect(float x, float y, float width, float height) {
	
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_frameBufferObject);

	glm::mat4 projection = glm::ortho(0.0f, (float)m_screenWidth, (float)m_screenHeight, 0.0f, -1.0f, 1.0f);	

	glm::mat4 model(1.0f);
	
	model = glm::translate(model, glm::vec3(x,y,0.0f));
	model = glm::scale(model, glm::vec3(width, height, 1.0f));

	GLint projLoc = glGetUniformLocation(m_frameBufferProgram, "u_projection");
	GLint modelLoc = glGetUniformLocation(m_frameBufferProgram, "u_model");
	
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(m_quadVAO);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
};


void Renderer::postProcess(float x, float y, float width, float height) {
	
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	
	glm::mat4 projection = glm::ortho(0.0f, (float)m_screenWidth, (float)m_screenHeight, 0.0f, -1.0f, 1.0f);	

	glm::mat4 model(1.0f);
	
	model = glm::translate(model, glm::vec3(x,y,0.0f));
	model = glm::scale(model, glm::vec3(width, height, 1.0f));

	int samplerLocation = glGetUniformLocation(m_defaultBufferProgram, "gSampler");
	GLint projLoc = glGetUniformLocation(m_defaultBufferProgram, "u_projection");
	GLint modelLoc = glGetUniformLocation(m_defaultBufferProgram, "u_model");
	
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniform1i(samplerLocation, 0);

	glBindVertexArray(m_quadVAO);
	glBindTexture(GL_TEXTURE_2D, m_frameBufferTexture);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
};


void Renderer::shutdown() {
	if (m_quadEBO) {
		glDeleteBuffers(1, &m_quadEBO);	
		m_quadEBO = 0;
	}
	if (m_quadVBO) {
		glDeleteBuffers(1, &m_quadVBO);	
		m_quadVBO = 0;
	}
	if (m_quadVAO) {
		glDeleteVertexArrays(1, &m_quadVAO);	
		m_quadVAO = 0;
	}
	if (m_frameBufferProgram) {
		glDeleteProgram(m_frameBufferProgram);
		m_frameBufferProgram = 0;
	}
}

Renderer::Renderer() : 
	m_frameBufferProgram(0),
	m_quadVAO(0),
	m_quadVBO(0),
	m_quadEBO(0),	

	m_screenWidth(800),
	m_screenHeight(600) {}

Renderer::~Renderer() {
	shutdown();
}


