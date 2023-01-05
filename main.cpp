#include <iostream>
#include <SFML/Graphics.hpp>

#include "player/player.hpp"

int main(int argc, char* argv[])
{
    const int WIDTH = 800; // window width
    const int HEIGHT = 600; // window height
    
    const float STEPSIZE = 6.f; // step size for player

    float x = 400; // x spawn point ball
    float y = 300; // y spawn point ball
    
    float r = 20; // radius ball

    float dx = 6; // x speed ball
    float dy = 2; // y speed ball

    bool flagForPause = false;
    bool flagForLeftOrRightMoveBall = false;

    int firstWins = 0; // number of wins first player
    int secondWins = 0; // number of wins first player

    sf::RenderWindow win(sf::VideoMode(WIDTH, HEIGHT), "ping-pong");

    sf::CircleShape ball(0);
    ball.setFillColor(sf::Color::White);
    ball.setRadius(r);
    ball.setOrigin(r, r);


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

        // victory conditions
        if (x + r > WIDTH)
        {
            dx = 0;
            dy = 0;
            x = 400.f;
            y = 300.f;
            flagForPause = true;
    		flagForLeftOrRightMoveBall = true;
            std::cout << "Win left" << std::endl;
        }

        if (x - r < 0)
        {
            dx = 0;
            dy = 0;
            x = 400.f;
            y = 300.f;
            flagForPause = true;
            flagForLeftOrRightMoveBall = false;
            std::cout << "Win right" << std::endl;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if (flagForLeftOrRightMoveBall)
                    dx = 6;
                else
                    dx = -6;
                dy = 2;
                flagForPause = false;
            }

        
        // ball move
        if(!flagForPause)
        {
            x += dx;
    	    y += dy;
    	}
        
        if ((y + r > HEIGHT) || (y - r < 0))
    		dy = -dy;
        
        if ((x + r <= (firstPlayer.getX()+50)) && ((firstPlayer.getY() <= (y + r)) && ((y + r) <= (firstPlayer.getY() + 200.f))))
    	    dx = -dx;
        
        if ((x + r >= (secondPlayer.getX()+5)) && ((secondPlayer.getY() <= (y + r)) && ((y + r) <= (secondPlayer.getY() + 200.f))))
    	    dx = -dx;

        // standard position for ball
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
        {   
            x = 400.f;
            y = 300.f;
        }

        // set position for ball
        ball.setPosition(x, y);


        // first player control
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && !(firstPlayer.getY()-STEPSIZE <= 0))
            firstPlayer.setY(firstPlayer.getY() - STEPSIZE);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !(firstPlayer.getY()+STEPSIZE >= 400))
            firstPlayer.setY(firstPlayer.getY() + STEPSIZE);

        // set position for first player shape
        firstPlayerShape.setPosition(firstPlayer.getX(), firstPlayer.getY());


        // second player control
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && !(secondPlayer.getY()-STEPSIZE <= 0))
            secondPlayer.setY(secondPlayer.getY() - STEPSIZE);
        
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && !(secondPlayer.getY()+STEPSIZE >= 400))
            secondPlayer.setY(secondPlayer.getY() + STEPSIZE);

        // set position for second player shape
        secondPlayerShape.setPosition(secondPlayer.getX(), secondPlayer.getY());



        // draw field
        win.clear(sf::Color::Black);

        // draw ball
        win.draw(ball);

        // draw first player shape
        win.draw(firstPlayerShape);
        
        // draw second player shape
        win.draw(secondPlayerShape);


        win.display();


    }
    return 0;
}