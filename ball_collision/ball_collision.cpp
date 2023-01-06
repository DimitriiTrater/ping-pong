#include "ball_collision.hpp"
void collisionBallY(float& dy, Ball& ball, int HEIGHT)
{
    if ((ball.getY() + ball.getR() > HEIGHT) || (ball.getY() - ball.getR() < 0))
        dy = -dy;
}

void collisionBallXForLeft(float& dx, Ball& ball, Player& firstPlayer, float& extraSpeed)
{
    if ((ball.getX() + ball.getR() <= (firstPlayer.getX()+60)) && ((firstPlayer.getY() <= (ball.getY() + ball.getR())) && ((ball.getY() + ball.getR()) <= (firstPlayer.getY() + 200.f))))
    {   
        extraSpeed += 0.1;
        if (dx < 0) 
            dx = -(dx - extraSpeed);
        else if (dx > 0)
            dx = -(dx + extraSpeed);
    }
}

void collisionBallXForRight(float& dx, Ball& ball, Player& secondPlayer, float& extraSpeed)
{
    if ((ball.getX() + ball.getR() >= (secondPlayer.getX()-3)) && ((secondPlayer.getY() <= (ball.getY() + ball.getR())) && ((ball.getY() + ball.getR()) <= (secondPlayer.getY() + 200.f))))
    {   
        extraSpeed += 0.1;
        if (dx < 0) 
            dx = -(dx - extraSpeed);
        else if (dx > 0)
            dx = -(dx + extraSpeed);
    }
}