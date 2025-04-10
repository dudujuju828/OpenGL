
#include "../include/Vector.h"
#include "../include/Game.h"
#include "../include/Paddle.h"
#include "../include/Ball.h"
#include "../include/AudioEngine.h"

#include <algorithm>
#include <cmath>
#include <iostream>

Paddle::Paddle() : 
	m_position(0.0f,0.0f),
	m_dimensions(0.0f,0.0f),
	m_speed(0.0f),
	m_defaultSpeed(0.0f)
{}

Paddle::Paddle(float x, float y, float width, float height, float speed) : 
		m_position(x, y),
		m_speed(speed),
		m_defaultSpeed(speed),
		m_dimensions(width,height)
		{}
	
void Paddle::setY(float value) {
	m_position.y = value;	
}

void Paddle::clamp(float screenHeight) {
	m_position.y = std::clamp(m_position.y, 0.0f, static_cast<float>(screenHeight - m_dimensions.y));
}

void Paddle::setSpeed(float value) {
	m_speed = value;
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
		AudioEngine* g_audio_instance = AudioEngine::getInstance();
		g_audio_instance->playWav("src/audio/rebound.wav");

		ball.x = rightX + ball.radius;
		ball.velX = std::fabs(ball.velX);
		// take the difference between the center of the paddle and the ball's y
		float diff = (m_position.y + (m_dimensions.y /2.0f)) - ball.y; // if this value is negative, the ball is below the center of the paddle
		float amplitude = 10.0f;
		ball.velY = diff * amplitude + ball.velY;
		
		// now to progress the game, increase both vely and velx by proportional amounts
		ball.velX += ball.velX / 50.0f;
		ball.velY += ball.velY / 50.0f;
		if (m_speed < 800.0f) m_speed += m_speed / 50.0f;
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

		AudioEngine* g_audio_engine = AudioEngine::getInstance();
		g_audio_engine->playWav("src/audio/rebound.wav");

		ball.x = leftX - ball.radius;
		ball.velX = -std::fabs(ball.velX);
		// take the difference between the center of the paddle and the ball's y
		float diff = (m_position.y + (m_dimensions.y /2.0f)) - ball.y; // if this value is negative, the ball is below the center of the paddle
		float amplitude = 10.0f;
		ball.velY = diff * amplitude + ball.velY;

		// now to progress the game, increase both vely and velx by proportional amounts
		ball.velX += ball.velX / 50.0f;
		ball.velY += ball.velY / 50.0f;
		if (m_speed < 800.0f) m_speed += m_speed / 50.0f;
	}			
}

