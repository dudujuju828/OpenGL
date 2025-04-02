#version 330 core
		
		out vec4 FragColor;		
		in vec2 texCoords;
		
		uniform bool textureOn;
		uniform sampler2D gSampler;
		uniform vec3 rectColor;
		

		
		void main() {
			if (!textureOn) {
				FragColor = vec4(rectColor,1.0f);
			} else {
				FragColor = texture(gSampler, texCoords);
			}
		}
