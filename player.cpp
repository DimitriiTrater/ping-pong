#include "Player.hpp"


Player::Player(float x, float y) // constructor
{
    this->x = x;
    this->y = y;
}


void Player::setX(float x) // set x position
{this->x = x;}

void Player::setY(float y) // set y position
{this->y = y;}


float Player::getX() // get x position
{return this->x;}

float Player::getY() // get y position
{return this->y;}

