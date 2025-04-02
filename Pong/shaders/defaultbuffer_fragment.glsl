#version 330 core
		
		out vec4 FragColor;		
		in vec2 texCoords;

		uniform sampler2D gSampler;
		
		void main() {
			FragColor = texture(gSampler, texCoords);
		}
