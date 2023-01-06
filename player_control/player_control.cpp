#include "player_control.hpp"

void playerControll(Player& player, const float& STEPSIZE, const sf::Keyboard::Key& Up, const sf::Keyboard::Key& Down)
{
        if ((sf::Keyboard::isKeyPressed(Up)) && !(player.getY()-STEPSIZE <= 0))
            player.setY(player.getY() - STEPSIZE);

        if (sf::Keyboard::isKeyPressed(Down) && !(player.getY()+STEPSIZE >= 400))
            player.setY(player.getY() + STEPSIZE);
}
