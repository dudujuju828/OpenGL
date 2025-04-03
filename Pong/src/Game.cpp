
#include "../include/Game.h"
#include "../include/Window.h"
#include "../include/Texture.h"

#include "../include/Paddle.h"
#include "../include/Ball.h"

#include <algorithm>
#include <iostream>
#include <cmath>     
#include <random>

Game::Game()
    : m_scoreLeft(0)
    , m_scoreRight(0)
	, m_checkerWidth(3)
	, m_checkerHeight(20)
    , m_screenWidth(1920)
    , m_screenHeight(1080)
	, m_ball(m_screenWidth * 0.5f, m_screenHeight * 0.5f, 7.0f, 1400.0f, 240.0f)
	, m_distrib(-2.0f, 2.0f)
	, m_paused(false)
	, m_previously_paused(false)
	, m_ai_on(true)
	, m_ai_previously_on(false)
{
}

Game::~Game() {
}

void Game::initPaddles(float width, float height, float speed) {

	float fixed_x_distance = 50.0f;

	Paddle leftPaddle(fixed_x_distance, m_screenHeight * 0.5f - height/2.0f, width, height, speed*1.6f);

	Paddle rightPaddle(static_cast<float>(m_screenWidth) - (width + fixed_x_distance),
										  m_screenHeight * 0.5f - height/2.0f, width, height, speed*1.6f);
	
	m_leftPaddle = leftPaddle;

	m_rightPaddle = rightPaddle;
}

void Game::init(const Window &window) {
    m_screenWidth = window.getWidth();
    m_screenHeight = window.getHeight();
	
	std::random_device rd;
	std::mt19937 gen(rd());
	m_generator = gen;
	
	m_ball.x = m_screenWidth;
	m_ball.y = m_screenHeight;

	initPaddles(20.0f, 100.0f, 600.0f);
}

void Game::update(Input& input, Window& window, float dt) {
    if (input.isPressed(Key::W)) {
        m_leftPaddle.setY(m_leftPaddle.getY() - (m_leftPaddle.getSpeed() * dt));
    }
    if (input.isPressed(Key::S)) {
        m_leftPaddle.setY(m_leftPaddle.getY() + (m_leftPaddle.getSpeed() * dt));
    }

    if (input.isPressed(Key::Up)) {
        m_rightPaddle.setY(m_rightPaddle.getY() - (m_rightPaddle.getSpeed() * dt));
    }
    if (input.isPressed(Key::Down)) {
        m_rightPaddle.setY(m_rightPaddle.getY() + (m_rightPaddle.getSpeed() * dt));
    }
	bool zeroPressed = input.isPressed(Key::Zero);
	if (input.isPressed(Key::Zero) && !m_ai_previously_on) {
		if (m_ai_on) { m_leftPaddle.setSpeed( m_leftPaddle.getSpeed() / 1.6f); }
		else { m_leftPaddle.setSpeed( m_leftPaddle.getSpeed() * 1.6f); }
		m_ai_on = !m_ai_on;
	}

	if (input.isPressed(Key::Escape)) {
		window.setShouldClose(true);
	}
	bool spacePressed = input.isPressed(Key::Space);
	if (input.isPressed(Key::Space) && !m_previously_paused) {
		m_paused = !m_paused;
	}
	
	// left paddle will be assumed to be AI
	// simple algorithm, compare Y's, and if ball on ai's side
	// basically undefeatable right now // add more sampling points for more natural
	float random_val = 2.1f + m_distrib(m_generator);
	if (m_ai_on) {

	if ((m_ball.x < static_cast<float>(m_screenWidth / 2.0f) || m_ball.x > static_cast<float>(m_screenWidth / 1.5f)) 
		&& (std::fabs(((m_leftPaddle.getY() + m_leftPaddle.getHeight()/2.0f)) - m_ball.y)) > (m_leftPaddle.getHeight() / (random_val)) ) {
			if (m_leftPaddle.getY() + static_cast<float>(m_leftPaddle.getHeight() / 2.0f)  > m_ball.y) {
				m_leftPaddle.setY(m_leftPaddle.getY() - (m_leftPaddle.getSpeed() * dt));
			} else {
				m_leftPaddle.setY(m_leftPaddle.getY() + (m_leftPaddle.getSpeed() * dt));
			}
		}

	} // ai end 
	
	
	m_leftPaddle.clamp(m_screenHeight);
	m_rightPaddle.clamp(m_screenHeight);
	

	if (!m_paused) m_ball.update(m_screenHeight, m_screenWidth, dt, m_leftPaddle, m_rightPaddle, random_val);
	
	m_previously_paused = spacePressed;
	m_ai_previously_on = zeroPressed;

	m_leftPaddle.checkCollisionLeft(m_ball);
	m_rightPaddle.checkCollisionRight(m_ball);
 
}

void Game::drawCheckers(Renderer &renderer) {
	int y_position = static_cast<float>(m_checkerHeight/2.0f);
	while (y_position < m_screenHeight) {
		renderer.drawRect(m_screenWidth / 2, y_position, m_checkerWidth, m_checkerHeight);
		y_position += m_checkerHeight * 2;
	}
}

void Game::render(Renderer& renderer, Window& window, Input& input, float dt) {
	
	input.pollEvents(window);

	update(input, window, dt);	

	renderer.clear();

	renderer.useProgram(renderer.getDefaultbufferProgram());
	renderer.setDefaultbufferFloat("time",window.getTime());
	
	renderer.useProgram(renderer.getFramebufferProgram());
	renderer.setFramebufferVec3("rectColor",0.1f,0.1f,0.1f);
	
//	renderer.drawBackdrop(0, 0, m_screenWidth, m_screenHeight);
	renderer.drawRect(0,0,m_screenWidth,m_screenHeight);

	renderer.setFramebufferVec3("rectColor",1.0f,1.0f,1.0f);
    renderer.drawRect(m_leftPaddle.getX(), m_leftPaddle.getY(), 
                      m_leftPaddle.getWidth(), m_leftPaddle.getHeight());

    renderer.drawRect(m_rightPaddle.getX(), m_rightPaddle.getY(), 
                      m_rightPaddle.getWidth(), m_rightPaddle.getHeight());

    renderer.drawRect(m_ball.x - m_ball.radius, 
                      m_ball.y - m_ball.radius, 
                      m_ball.radius * 2.0f, 
                      m_ball.radius * 2.0f);
	
	drawCheckers(renderer);

	
	renderer.useProgram(renderer.getDefaultbufferProgram());
	renderer.postProcess(0,0,m_screenWidth,m_screenHeight,window);
	
	window.swapBuffers();
}
