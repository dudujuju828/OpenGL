
#pragma once

#include "Paddle.h"

class Ball {
public:
	Ball(float x, float y, float radius, float velX, float velY) : x(x), y(y), radius(radius), velX(velX), velY(velY), defaultVelX(velX), defaultVelY(velY) {}


	float x;
	float y;
	float radius;
	float velX;
	float velY;

	float defaultVelX;
	float defaultVelY;

	void update(float screen_height, float screen_width, float dt, Paddle &leftPaddle, Paddle &rightPaddle, float random_value);
};
