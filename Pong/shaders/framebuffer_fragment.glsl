#version 330 core
		
		out vec4 FragColor;		
		in vec2 texCoords;
		
		uniform bool textureOn;
		uniform sampler2D gSampler;
		
		void main() {
			if (!textureOn) {
				FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
			} else {
				FragColor = texture(gSampler, texCoords);
			}
		}
