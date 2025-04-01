#pragma once 

#include "Input.h"     
#include "Renderer.h" 
#include "Window.h"
#include "Texture.h"
#include "Ball.h"

#include "Paddle.h"

class Game {
public:
    Game(); 

    ~Game();  

    void init(const Window &window);

    void render(Renderer& renderer, Window& window, Input& input, float dt);

	float getBallVelX() const { return m_ball.velX; }
	float getBallVelY() const { return m_ball.velY; }

private:

    void update(Input& input, Window& window, float dt);

	void initPaddles(float width, float height, float speed);

	void drawCheckers(Renderer &renderer);

    Paddle m_leftPaddle; 
    Paddle m_rightPaddle;

    Ball   m_ball;         

    int    m_scoreLeft;  

    int    m_scoreRight; 

    int    m_screenWidth; 

    int    m_screenHeight; 
	
	int    m_checkerWidth;

	int    m_checkerHeight;
	
	Texture m_backdropTexture;
};
