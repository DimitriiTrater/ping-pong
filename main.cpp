#include <iostream>
#include <SFML/Graphics.hpp>

#include "player/player.hpp"
#include "ball/ball.hpp"

int main(int argc, char* argv[])
{
    const int WIDTH = 800; // window width
    const int HEIGHT = 600; // window height
    
    const float STEPSIZE = 6.f; // step size for player

    float dx = 6; // x speed ball
    float dy = 2; // y speed ball

    bool flagForPause = false; // flag for pause after failure
    bool flagForLeftOrRightMoveBall = false; // flag for left move or right move

    int firstWins = 0; // number of wins first player
    int secondWins = 0; // number of wins first player


    // ball create
    Ball ball(400.f, 300.f, 20.f);
    sf::CircleShape ballShape(0);
    ballShape.setFillColor(sf::Color::White);
    ballShape.setRadius(ball.getR());
    ballShape.setOrigin(ball.getR(), ball.getR());


    // first player create
    Player firstPlayer(0.f, 200.f);
    sf::RectangleShape firstPlayerShape(sf::Vector2f(20.f, 200.f));


    // second player create
    Player secondPlayer(780.f, 200.f);
    sf::RectangleShape secondPlayerShape(sf::Vector2f(20.f, 200.f));

    // win create
    sf::RenderWindow win(sf::VideoMode(WIDTH, HEIGHT), "ping-pong");
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
        if (ball.getX() + ball.getR() > WIDTH)
        {
            dx = 0;
            dy = 0;
            ball.setX(400.f);
            ball.setY(300.f);
            flagForPause = true;
    		flagForLeftOrRightMoveBall = true;
            std::cout << "Win left" << std::endl;
        }

        if (ball.getX() - ball.getR() < 0)
        {
            dx = 0;
            dy = 0;
            ball.setX(400.f);
            ball.setY(300.f);
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
    	    ball.setX(ball.getX()+dx);
    	    ball.setY(ball.getY()+dy);
        }
        
        if ((ball.getY() + ball.getR() > HEIGHT) || (ball.getY() - ball.getR() < 0))
    		dy = -dy;
        
        if ((ball.getX() + ball.getR() <= (firstPlayer.getX()+50)) && ((firstPlayer.getY() <= (ball.getY() + ball.getR())) && ((ball.getY() + ball.getR()) <= (firstPlayer.getY() + 200.f))))
    	    dx = -dx;
        
        if ((ball.getX() + ball.getR() >= (secondPlayer.getX()+5)) && ((secondPlayer.getY() <= (ball.getY() + ball.getR())) && ((ball.getY() + ball.getR()) <= (secondPlayer.getY() + 200.f))))
    	    dx = -dx;

        // standard position for ball
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
        {   
            ball.setX(400.f);
            ball.setY(300.f);
        }

        // set position for ball shape
        ballShape.setPosition(ball.getX(), ball.getY());


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
        win.draw(ballShape);

        // draw first player shape
        win.draw(firstPlayerShape);
        
        // draw second player shape
        win.draw(secondPlayerShape);


        win.display();


    }
    return 0;
}