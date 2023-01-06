#include <iostream>
#include <SFML/Graphics.hpp>

#include "player/player.hpp"
#include "ball/ball.hpp"



void collisionBallY(float& dy, Ball& ball, int HEIGHT)
{
    if ((ball.getY() + ball.getR() > HEIGHT) || (ball.getY() - ball.getR() < 0))
        dy = -dy;
}



int main(int argc, char* argv[])
{
    const int WIDTH = 800; // window width
    const int HEIGHT = 600; // window height
    
    const float STEPSIZE = 6.f; // step size for player

    float dx = 6; // x speed ball
    float dy = 2; // y speed ball
    float extraSpeed = 0; // extra speed for dx

    bool flagForPause = false; // flag for pause after failure
    bool flagForLeftOrRightMoveBall = false; // flag for left move or right move

    int firstWins = 0; // number of wins first player
    int secondWins = 0; // number of wins first player

    const sf::Color white = sf::Color::White; // white color

    // font
    sf::Font font;
    font.loadFromFile("C:\\Users\\1\\CLionProjects\\game\\sansation.ttf");
    
    // text for score
    sf::Text textLeft;
    sf::Text textRight;
    textLeft.setFont(font);
    textRight.setFont(font);
    textLeft.setString(std::to_string(firstWins));
    textRight.setString(std::to_string(secondWins));
    textLeft.setCharacterSize(24);
    textRight.setCharacterSize(24);
    textLeft.setFillColor(white);
    textRight.setFillColor(white);
    textLeft.setPosition(350.f, 0.f);
    textRight.setPosition(430.f, 0.f);

    // text for win
    sf::Text winText;
    winText.setFont(font);
    winText.setCharacterSize(50);
    winText.setFillColor(white);
    winText.setPosition(330.f, 200.f);
    

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

        // text update
        textLeft.setString(std::to_string(firstWins));
        textRight.setString(std::to_string(secondWins));

        // victory conditions
        if (ball.getX() + ball.getR() > WIDTH)
        {
            extraSpeed = 0;
            dx = 0;
            dy = 0;
            ball.setX(400.f);
            ball.setY(300.f);
            flagForPause = true;
    		flagForLeftOrRightMoveBall = true;
            std::cout << "Win left" << std::endl;
            firstWins++;
        }

        if (ball.getX() - ball.getR() < 0)
        {
            extraSpeed = 0;
            dx = 0;
            dy = 0;
            ball.setX(400.f);
            ball.setY(300.f);
            flagForPause = true;
            flagForLeftOrRightMoveBall = false;
            std::cout << "Win right" << std::endl;
            secondWins++;
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

        if (firstWins == 11)
            winText.setString("Win left");
       
        if (secondWins == 11)
            winText.setString("Win right");


        
        // ball move
        if(!flagForPause)
        {
    	    ball.setX(ball.getX()+dx);
    	    ball.setY(ball.getY()+dy);
        }
        
        collisionBallY(dy, ball, HEIGHT);
        
        if ((ball.getX() + ball.getR() <= (firstPlayer.getX()+50)) && ((firstPlayer.getY() <= (ball.getY() + ball.getR())) && ((ball.getY() + ball.getR()) <= (firstPlayer.getY() + 200.f))))
    	{   
            extraSpeed += 0.1;
            if (dx < 0) 
                dx = -(dx - extraSpeed);
            else if (dx > 0)
                dx = -(dx + extraSpeed);
        }

        if ((ball.getX() + ball.getR() >= (secondPlayer.getX()+5)) && ((secondPlayer.getY() <= (ball.getY() + ball.getR())) && ((ball.getY() + ball.getR()) <= (secondPlayer.getY() + 200.f))))
    	{   
            extraSpeed += 0.1;
            if (dx < 0) 
                dx = -(dx - extraSpeed);
            else if (dx > 0)
                dx = -(dx + extraSpeed);
        }


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

        // draw text
        win.draw(textLeft);
        win.draw(textRight);
        win.draw(winText);

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