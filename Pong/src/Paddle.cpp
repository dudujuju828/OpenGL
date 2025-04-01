
#include "../include/Vector.h"
#include "../include/Game.h"
#include "../include/Paddle.h"
#include "../include/Ball.h"

#include <algorithm>
#include <cmath>
#include <iostream>

Paddle::Paddle() : 
	m_position(0.0f,0.0f),
	m_dimensions(0.0f,0.0f),
	m_speed(0.0f)
{}

Paddle::Paddle(float x, float y, float width, float height, float speed) : 
		m_position(x, y),
		m_speed(400.0f),
		m_dimensions(width,height)
		{}
	
void Paddle::setY(float value) {
	m_position.y = value;	
}

void Paddle::clamp(float screenHeight) {
	m_position.y = std::clamp(m_position.y, 0.0f, static_cast<float>(screenHeight - m_dimensions.y));
}

void Paddle::checkCollisionLeft(Ball &ball) {
	float leftX = m_position.x;
	float rightX = m_position.x + m_dimensions.x;
	float lowerY = m_position.y + m_dimensions.y;
	float upperY = m_position.y;	

	bool collisionLeftPaddle = 
	(ball.x - ball.radius < rightX) &&
	(ball.x + ball.radius > leftX) &&
	(ball.y - ball.radius < lowerY) &&
	(ball.y + ball.radius > upperY);
		
	if (collisionLeftPaddle) {
		ball.x = rightX + ball.radius;
		ball.velX = std::fabs(ball.velX);
	}	
}

void Paddle::checkCollisionRight(Ball &ball) {
	float leftX = m_position.x;
	float rightX = m_position.x + m_dimensions.x;
	float lowerY = m_position.y + m_dimensions.y;
	float upperY = m_position.y;	

	bool collisionRightPaddle = 
	(ball.x + ball.radius > leftX) &&
	(ball.x - ball.radius < rightX) &&
	(ball.y - ball.radius < lowerY) &&
	(ball.y + ball.radius > upperY);

	if (collisionRightPaddle) {
		ball.x = leftX - ball.radius;
		ball.velX = -std::fabs(ball.velX);
	}			
}

