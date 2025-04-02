
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../include/Shader.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using std::string;

void Shader::checkShaderCompilation(unsigned int objectID) {
	int success;
	char infoLog[512];
	glGetShaderiv(objectID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(objectID, sizeof(infoLog), nullptr, infoLog);
		std::cerr << "ERROR: Shader compilation.\n" << infoLog;
	}
}

void Shader::checkProgramLinkage(unsigned int objectID) {
	int success;
	char infoLog[512];
	glGetShaderiv(objectID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(objectID, sizeof(infoLog), nullptr, infoLog);
		std::cerr << "ERROR: Program linking.\n" << infoLog;
	}
}


Shader::Shader(const char* vertex_shader_path, const char* fragment_shader_path) {

	std::ifstream vertex_file(vertex_shader_path);
	std::ifstream fragment_file(fragment_shader_path);

	string vertex_shader_source;
	string fragment_shader_source;
	
	if (vertex_file.is_open()) {
		std::stringstream vertex_stream;
		vertex_stream << vertex_file.rdbuf();
		vertex_shader_source = vertex_stream.str();	
	}	

	if (fragment_file.is_open()) {
		std::stringstream fragment_stream;
		fragment_stream << fragment_file.rdbuf();
		fragment_shader_source = fragment_stream.str();	
	}
	
	unsigned int vertex_shader_object = glCreateShader(GL_VERTEX_SHADER);	
	unsigned int fragment_shader_object = glCreateShader(GL_FRAGMENT_SHADER);	
	
	const char * vertex_cstyle_source = vertex_shader_source.c_str();
	const char * fragment_cstyle_source = fragment_shader_source.c_str();
	
	glShaderSource(vertex_shader_object, 1, &vertex_cstyle_source, nullptr);
	glShaderSource(fragment_shader_object, 1, &fragment_cstyle_source, nullptr);
	
	glCompileShader(vertex_shader_object);	
	glCompileShader(fragment_shader_object);	

	checkShaderCompilation(vertex_shader_object);
	checkShaderCompilation(fragment_shader_object);
	
	int program = glCreateProgram();
	glAttachShader(program, vertex_shader_object);
	glAttachShader(program, fragment_shader_object);
	glLinkProgram(program);
	
	checkProgramLinkage(program);
	
	m_programID = program;	
}
