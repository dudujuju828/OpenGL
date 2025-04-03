#version 330 core
		
out vec4 FragColor;		
in vec2 texCoords;

uniform sampler2D gSampler;
uniform float time;
		
void main() {
	vec2 centeredCoords = texCoords * 2 - 1.0f;	
	float k = 0.1;
	float r2 = dot(centeredCoords, centeredCoords);
	centeredCoords *= 1.0 + k * r2;
	vec2 finalTexCoord = (centeredCoords + 1.0) * 0.5;
		
	float width = 200.0f;
	float screenWidth = 1920;
	float screenHeight = 1080;
	float dist = length(finalTexCoord - vec2(0.5));
	float vignetteFactor = smoothstep(0.8,1.0,dist);
		
	vec4 color = texture(gSampler, finalTexCoord);
	color.g *= (sin(finalTexCoord.y * screenHeight * 0.5f) + 1.0f) * 0.25f + 1.0f;
	color.rb *= (cos(finalTexCoord.y * screenHeight * 0.5f) + 1.0f) * 0.235f + 1.0f;
			
	FragColor = color * (1.0 - vignetteFactor);
			
		
	if (finalTexCoord.x > 1.0f || finalTexCoord.x < 0.0f || finalTexCoord.y < 0.0f || 		 finalTexCoord.y > 1.0f) {
		FragColor = vec4(0.0f,0.0f,0.0f,1.0f);
	}
}
