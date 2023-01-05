#include <iostream>
#include <SFML/Graphics.hpp>

#include "player.hpp"

int main(int argc, char* argv[])
{
    const int W = 800; 
    const int H = 600;
    
    const float STEPSIZE = 6.f; // step size for player


    float x = 400; // x spawn point ball
    float y = 300; // y spawn point ball
    
    float r = 20; // radius ball

    float dx = 4; // x speed ball
    float dy = 2; // y speed ball


    sf::RenderWindow win(sf::VideoMode(W, H), "ping-pong");

    sf::CircleShape shape(0);

    // first player create
    Player firstPlayer(0.f, 200.f);
    sf::RectangleShape firstPlayerShape(sf::Vector2f(20.f, 200.f));

    // second player create
    Player secondPlayer(780.f, 200.f);
    sf::RectangleShape secondPlayerShape(sf::Vector2f(20.f, 200.f));


    win.setFramerateLimit(60);

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
            {
                win.close();
                std::cout << "log: win closed" << std::endl;
            }

            if (event.type == sf::Event::LostFocus)
                std::cout << "log: lost focus" << std::endl;

            if (event.type == sf::Event::GainedFocus)
                std::cout << "log: gained focus" << std::endl;
        }
        

        x += dx;
    	y += dy;
    	
        if ((y + r > H) || (y - r < 0))
    		dy = -dy;
        
        if ((x + r <= (firstPlayer.getX()+50)) && ((firstPlayer.getY() <= (y + r)) && ((y + r) <= (firstPlayer.getY() + 200.f))))
    	    dx = -dx;
        
        if ((x + r >= (secondPlayer.getX()+5)) && ((secondPlayer.getY() <= (y + r)) && ((y + r) <= (secondPlayer.getY() + 200.f))))
    	    dx = -dx;

        win.clear(sf::Color::Black);

        shape.setRadius(r);
        shape.setOrigin(r, r);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);
        win.draw(shape);


        // standard position for ball
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
        {   
            x = 400.f;
            y = 500.f;
        }

        // first player control
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && !(firstPlayer.getY()-STEPSIZE <= 0))
            firstPlayer.setY(firstPlayer.getY() - STEPSIZE);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !(firstPlayer.getY()+STEPSIZE >= 400))
            firstPlayer.setY(firstPlayer.getY() + STEPSIZE);

        // set position for first player
        firstPlayerShape.setPosition(firstPlayer.getX(), firstPlayer.getY());

        // draw first player shape
        win.draw(firstPlayerShape);

        // second player control
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && !(secondPlayer.getY()-STEPSIZE <= 0))
            secondPlayer.setY(secondPlayer.getY() - STEPSIZE);
        
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && !(secondPlayer.getY()+STEPSIZE >= 400))
            secondPlayer.setY(secondPlayer.getY() + STEPSIZE);

        // set position for second player
        secondPlayerShape.setPosition(secondPlayer.getX(), secondPlayer.getY());

        // draw second player shape
        win.draw(secondPlayerShape);
         

        win.display();


    }
    return 0;
}