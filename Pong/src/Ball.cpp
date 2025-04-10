
#include "../include/Ball.h"
#include "../include/Paddle.h"
#include "../include/AudioEngine.h"

void Ball::update(float screen_height, float screen_width, float dt, Paddle& leftPaddle, Paddle& rightPaddle, float random_value) {
	x += velX * dt;
	y += velY * dt;
	
	float offset_value = random_value - 2.1f;
	float initialVelY = (offset_value) * 300.0f;

	if (offset_value < 0.0f) { defaultVelX *= -1; }
	float additionVelX = (offset_value) * 200.0f;
	

	if (y - radius < 0.0f) {
		AudioEngine* g_aud_inst = AudioEngine::getInstance();
		g_aud_inst->playWav("src/audio/wallbounce.wav");
		y = radius;
		velY = -velY;
	} else if (y + radius > screen_height) {
		AudioEngine* g_aud_inst = AudioEngine::getInstance();
		g_aud_inst->playWav("src/audio/wallbounce.wav");	
		y = screen_height - radius;
		velY = -velY;
	}

	if (x + radius < 0.0f || x - radius > screen_width) {
		AudioEngine* g_aud_inst = AudioEngine::getInstance();
		g_aud_inst->playWav("src/audio/outofbound.wav");

		x = screen_width * 0.5f;
		y = screen_height * 0.5f;
		velX = defaultVelX + additionVelX;
		// 2.1f is the initial value added to the value
		// created by the distributor
		velY = initialVelY;
		leftPaddle.setSpeed(leftPaddle.getDefaultSpeed());
		rightPaddle.setSpeed(rightPaddle.getDefaultSpeed());
		leftPaddle.setY(y - leftPaddle.getHeight() / 2.0f);
		rightPaddle.setY(y - rightPaddle.getHeight() / 2.0f);
	} 
}		
