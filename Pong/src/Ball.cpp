
#include "../include/Ball.h"
#include "../include/Paddle.h"

void Ball::update(float screen_height, float screen_width, float dt, Paddle& leftPaddle, Paddle& rightPaddle) {
	x += velX * dt;
	y += velY * dt;

	if (y - radius < 0.0f) {
		y = radius;
		velY = -velY;
	} else if (y + radius > screen_height) {
		y = screen_height - radius;
		velY = -velY;
	}

	if (x + radius < 0.0f) {
		x = screen_width * 0.5f;
		y = screen_height * 0.5f;
		velX = defaultVelX;
		velY = defaultVelY;
		leftPaddle.setSpeed(leftPaddle.getDefaultSpeed());
		
	} 
	else if (x - radius > screen_width) {
		x = screen_width * 0.5f;
		y = screen_height * 0.5f;
		velX = -defaultVelX;
		velY = defaultVelY;
		leftPaddle.setSpeed(leftPaddle.getDefaultSpeed());
	}
}		
