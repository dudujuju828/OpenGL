
#pragma once

#include "Vector.h"
#include "Ball.h"

class Paddle {

	Vector2D m_position;	
	Vector2D m_dimensions;
	float m_speed;

public:
	Paddle(float x, float y, float width, float height, float speed);
	Paddle();
	
	float getY() { return m_position.y; }
	void setY(float value);
	float getSpeed() { return m_speed; }
	
	float getX() { return m_position.x; }
	float getWidth() { return m_dimensions.x; }
	float getHeight() { return m_dimensions.y; }
	
	void clamp(float screenHeight);
	void checkCollisionRight(Ball &ball);
	void checkCollisionLeft(Ball &ball);
};
