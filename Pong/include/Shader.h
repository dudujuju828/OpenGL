
#pragma once

class 

class Shader {
	unsigned int m_programID;
	static bool checkShaderCompilation(unsigned int objectID);	
	
public:
	Shader(const char *vertex_shader_path, const char *fragment_shader_path);
};
