#include <iostream>
#include "ball_collision.hpp"
void collisionBallY(float& dy, Ball& ball, int HEIGHT)
{
    if ((ball.getY() + ball.getR() > HEIGHT) || (ball.getY() - ball.getR() < 0))
        dy = -dy;
}

void collisionBallXForLeft(float& dx, Ball& ball, Player& firstPlayer, float& extraSpeed)
{
    if ((ball.getX() + ball.getR() <= (firstPlayer.getX()+64)) && ((firstPlayer.getY() <= (ball.getY() + ball.getR())) && ((ball.getY() + ball.getR()) <= (firstPlayer.getY() + 240.f))))
    {   
        if (extraSpeed < 1)
        {
            extraSpeed += 0.1;
            //std::cout << extraSpeed << std::endl;
        }
        if (dx < -15)
            dx = -(dx - extraSpeed);
        else 
            dx = -dx;
        
        //std::cout << dx << std::endl;
        
    }
}

void collisionBallXForRight(float& dx, Ball& ball, Player& secondPlayer, float& extraSpeed)
{
    if ((ball.getX() + ball.getR() >= (secondPlayer.getX())) && ((secondPlayer.getY() <= (ball.getY() + ball.getR())) && ((ball.getY() + ball.getR()) <= (secondPlayer.getY() + 240.f))))
    {   
        if (extraSpeed < 1)
        {
            extraSpeed += 0.1;
            //std::cout << extraSpeed << std::endl;
        }
        if (dx < 15)
            dx = -(dx + extraSpeed);
        else
            dx = -dx;
        //std::cout << dx << std::endl;
        
    }
}