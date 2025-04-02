	#version 330 core
		
		layout (location = 0) in vec4 aPos;
	
		uniform mat4 u_projection;
		uniform mat4 u_model;

		out vec2 texCoords;

		void main() {
			gl_Position = u_projection * u_model * vec4(aPos.xy, 0.0f, 1.0f);
			texCoords = aPos.zw;
		}
