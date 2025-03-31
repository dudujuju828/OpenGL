#pragma once 

#include "Input.h"     
#include "Renderer.h" 
#include "Window.h"
#include "Texture.h"

class Game {
public:
    Game(); 

    ~Game();  

    void init(const Window &window);

    void render(Renderer& renderer, Window& window, Input& input, float dt);

private:

    void update(Input& input, float dt);

    struct Paddle {
        float x;       
        float y;       
        float width;   
        float height;  
        float speed;   
    };

    struct Ball {
        float x;       
        float y;      
        float radius;  
        float velX; 
        float velY;
    };

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
