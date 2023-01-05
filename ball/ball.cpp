#include "ball.hpp"

Ball::Ball(float x, float y, float r)
{
    this->x = x;
    this->y = y;
    this->r = r;
}

void Ball::SetX(float x)
{this->x = x;}

void Ball::SetY(float y)
{this->y = y;}

void Ball::SetR(float r)
{this->r = r;}


float Ball::GetX()
{return this->x;}

float Ball::GetY()
{return this->y;}

float Ball::GetR()
{return this->r;}

