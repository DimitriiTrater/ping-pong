#include <SFML/Graphics.hpp>
#include "../player/player.hpp"
#include "../ball/ball.hpp"
#pragma once
void collisionBallY(float& dy, Ball& ball, int HEIGHT);
void collisionBallXForLeft(float& dx, Ball& ball, Player& firstPlayer, float& extraSpeed);
void collisionBallXForRight(float& dx, Ball& ball, Player& secondPlayer, float& extraSpeed);
