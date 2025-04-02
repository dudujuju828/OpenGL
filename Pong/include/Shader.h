
#pragma once

class Shader {
	unsigned int m_programID;
	void checkShaderCompilation(unsigned int objectID);	
	void checkProgramLinkage(unsigned int objectID);	
	
public:
	Shader(const char *vertex_shader_path, const char *fragment_shader_path);
	unsigned int getProgramID() const { return m_programID; }
};
