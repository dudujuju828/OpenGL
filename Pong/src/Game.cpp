

#include "../include/Game.h"

#include <algorithm>
#include <cmath>     

Game::Game()
    : m_scoreLeft(0)
    , m_scoreRight(0)
    , m_screenWidth(800)
    , m_screenHeight(600)
{
}

Game::~Game() {
}

void Game::init(int screenWidth, int screenHeight) {
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    m_scoreLeft  = 0;
    m_scoreRight = 0;

    m_leftPaddle.x = 50.0f;
    m_leftPaddle.y = m_screenHeight * 0.5f - 50.0f; 
    m_leftPaddle.width = 20.0f;
    m_leftPaddle.height = 100.0f;
    m_leftPaddle.speed = 300.0f; 

    m_rightPaddle = m_leftPaddle;
    m_rightPaddle.x = static_cast<float>(m_screenWidth) - 70.0f; 

    m_ball.x = m_screenWidth * 0.5f;
    m_ball.y = m_screenHeight * 0.5f;
    m_ball.radius = 10.0f;
    m_ball.velX = 200.0f; 
    m_ball.velY = 120.0f; 
}

void Game::update(const Input& input, float dt) {
    if (input.isPressed(Key::W)) {
        m_leftPaddle.y -= m_leftPaddle.speed * dt;
    }
    if (input.isPressed(Key::S)) {
        m_leftPaddle.y += m_leftPaddle.speed * dt;
    }

    if (input.isPressed(Key::Up)) {
        m_rightPaddle.y -= m_rightPaddle.speed * dt;
    }
    if (input.isPressed(Key::Down)) {
        m_rightPaddle.y += m_rightPaddle.speed * dt;
    }

    m_leftPaddle.y  = std::clamp(m_leftPaddle.y, 0.0f, static_cast<float>(m_screenHeight - m_leftPaddle.height));
    m_rightPaddle.y = std::clamp(m_rightPaddle.y, 0.0f, static_cast<float>(m_screenHeight - m_rightPaddle.height));

    m_ball.x += m_ball.velX * dt;
    m_ball.y += m_ball.velY * dt;

    if (m_ball.y - m_ball.radius < 0.0f) {
        m_ball.y = m_ball.radius;
        m_ball.velY = -m_ball.velY;
    } else if (m_ball.y + m_ball.radius > m_screenHeight) {
        m_ball.y = m_screenHeight - m_ball.radius;
        m_ball.velY = -m_ball.velY;
    }

    if (m_ball.x + m_ball.radius < 0.0f) {
        m_scoreRight++;
        m_ball.x = m_screenWidth * 0.5f;
        m_ball.y = m_screenHeight * 0.5f;
        m_ball.velX = 200.0f;
        m_ball.velY = 120.0f;
    } 
    else if (m_ball.x - m_ball.radius > m_screenWidth) {
        m_scoreLeft++;
        m_ball.x = m_screenWidth * 0.5f;
        m_ball.y = m_screenHeight * 0.5f;
        m_ball.velX = -200.0f;
        m_ball.velY = 120.0f;
    }

    float lpLeft   = m_leftPaddle.x;
    float lpRight  = m_leftPaddle.x + m_leftPaddle.width;
    float lpTop    = m_leftPaddle.y;
    float lpBottom = m_leftPaddle.y + m_leftPaddle.height;

    bool collisionLeftPaddle = 
        (m_ball.x - m_ball.radius < lpRight) &&
        (m_ball.x + m_ball.radius > lpLeft) &&
        (m_ball.y - m_ball.radius < lpBottom) &&
        (m_ball.y + m_ball.radius > lpTop);

    if (collisionLeftPaddle) {
        m_ball.x = lpRight + m_ball.radius;
        m_ball.velX = std::fabs(m_ball.velX);
    }

    // Right paddle bounding box
    float rpLeft   = m_rightPaddle.x;
    float rpRight  = m_rightPaddle.x + m_rightPaddle.width;
    float rpTop    = m_rightPaddle.y;
    float rpBottom = m_rightPaddle.y + m_rightPaddle.height;

    bool collisionRightPaddle = 
        (m_ball.x + m_ball.radius > rpLeft) &&
        (m_ball.x - m_ball.radius < rpRight) &&
        (m_ball.y - m_ball.radius < rpBottom) &&
        (m_ball.y + m_ball.radius > rpTop);

    if (collisionRightPaddle) {
        m_ball.x = rpLeft - m_ball.radius;
        m_ball.velX = -std::fabs(m_ball.velX);
    }
}

void Game::render(Renderer& renderer) {
    renderer.drawRect(m_leftPaddle.x, m_leftPaddle.y, 
                      m_leftPaddle.width, m_leftPaddle.height);

    renderer.drawRect(m_rightPaddle.x, m_rightPaddle.y, 
                      m_rightPaddle.width, m_rightPaddle.height);

    renderer.drawRect(m_ball.x - m_ball.radius, 
                      m_ball.y - m_ball.radius, 
                      m_ball.radius * 2.0f, 
                      m_ball.radius * 2.0f);
}
