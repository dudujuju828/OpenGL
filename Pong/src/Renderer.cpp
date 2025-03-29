
#include "../include/Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

static bool checkShaderCompilation(unsigned int shaderID, const std::string& type) {
	int success;
	char infoLog[1024];	
	if (type == "PROGRAM") {
		glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << std::endl;
			return false;
		} 
	} else {
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR\n" << infoLog << std::endl;
			return false;
		}
	}
	return true;
}

bool Renderer::init(int screenWidth, int screenHeight) {
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	
	const char* vertexShaderSrc = R"(
		#version 330 core
		
		layout (location = 0) in vec2 aPos;
	
		uniform mat4 u_projection;
		uniform mat4 u_model;

		void main() {
			gl_Position = u_projection * u_model * vec4(aPos, 0.0f, 1.0f);
		}
	)";	

	const char* fragmentShaderSrc = R"(
		#version 330 core
		
		out vec4 FragColor;		
		
		void main() {
			FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
		}
	)";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);	
	glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
	glCompileShader(vertexShader);
	if (!checkShaderCompilation(vertexShader, "VERTEX")) {
		return false;
	}
	
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
	glCompileShader(fragmentShader);
	if (!checkShaderCompilation(fragmentShader, "FRAGMENT")) {
		return false;
	}

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);
	if (!checkShaderCompilation(m_shaderProgram, "PROGRAM")) {
		return false;
	}
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
	
	glBindVertexArray(0);

	return true;

}

void Renderer::clear() {
	glClearColor(0.2f,0.2f,0.2f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawRect(float x, float y, float width, float height) {
	glUseProgram(m_shaderProgram);
	
	glm::mat4 projection = glm::ortho(0.0f, (float)m_screenWidth, (float)m_screenHeight, 0.0f, -1.0f, 1.0f);	

	glm::mat4 model(1.0f);
	
	model = glm::translate(model, glm::vec3(x,y,0.0f));
	model = glm::scale(model, glm::vec3(width, height, 1.0f));

	GLint projLoc = glGetUniformLocation(m_shaderProgram, "u_projection");
	GLint modelLoc = glGetUniformLocation(m_shaderProgram, "u_model");
	
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(m_quadVAO);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
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
	if (m_shaderProgram) {
		glDeleteProgram(m_shaderProgram);
		m_shaderProgram = 0;
	}
}

Renderer::Renderer() : 
	m_shaderProgram(0),
	m_quadVAO(0),
	m_quadVBO(0),
	m_quadEBO(0),	

	m_screenWidth(800),
	m_screenHeight(600) {}

Renderer::~Renderer() {
	shutdown();
}
