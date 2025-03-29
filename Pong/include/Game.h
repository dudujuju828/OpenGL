#pragma once 

#include "Input.h"     
#include "Renderer.h" 

class Game {
public:
    Game(); 

    ~Game();  

    void init(int screenWidth, int screenHeight);

    void update(const Input& input, float dt);

    void render(Renderer& renderer);

private:

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
};

