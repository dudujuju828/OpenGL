
#include "../include/Game.h"
#include "../include/Window.h"
#include "../include/Texture.h"

#include "../include/Paddle.h"
#include "../include/Ball.h"

#include <algorithm>
#include <cmath>     

Game::Game()
    : m_scoreLeft(0)
    , m_scoreRight(0)
	, m_checkerWidth(10)
	, m_checkerHeight(20)
    , m_screenWidth(800)
    , m_screenHeight(600)
	, m_ball(m_screenWidth * 0.5f, m_screenHeight * 0.5f, 10.0f, 800.0f, 480.0f)
{
}

Game::~Game() {
}

void Game::initPaddles(float width, float height, float speed) {

	float fixed_x_distance = 50.0f;

	Paddle leftPaddle(fixed_x_distance, m_screenHeight * 0.5f - height/2.0f, width, height, speed);

	Paddle rightPaddle(static_cast<float>(m_screenWidth) - (width + fixed_x_distance),
										  m_screenHeight * 0.5f - height/2.0f, width, height, speed);
	
	m_leftPaddle = leftPaddle;
	m_rightPaddle = rightPaddle;
}

void Game::init(const Window &window) {
    m_screenWidth = window.getWidth();
    m_screenHeight = window.getHeight();

	initPaddles(20.0f, 70.0f, 200.0f);
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
	
	if (input.isPressed(Key::Escape)) {
		window.setShouldClose(true);
	}
	
	m_leftPaddle.clamp(m_screenHeight);
	m_rightPaddle.clamp(m_screenHeight);

	m_ball.update(m_screenHeight, m_screenWidth, dt);

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
	
	renderer.useProgram(renderer.getFramebufferProgram());
	
	renderer.drawBackdrop(0, 0, m_screenWidth, m_screenHeight);

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
	renderer.postProcess(0,0,m_screenWidth,m_screenHeight);
	
	window.swapBuffers();
}
