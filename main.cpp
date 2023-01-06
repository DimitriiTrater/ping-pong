#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>

#include "player/player.hpp"
#include "player_control/player_control.hpp"

#include "ball/ball.hpp"
#include "ball_collision/ball_collision.hpp"

void setParametersTextScore(sf::Text& text, const sf::Color color, sf::Font& font, int size, float x, float y)
{
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
}

int main(int argc, char* argv[])
{
    const int WIDTH = 800; // window width
    const int HEIGHT = 600; // window height
    
    const float STEPSIZE = 6.f; // step size for player

    float dx = 0; // x speed ball
    float dy = 0; // y speed ball
    float extraSpeed = 0; // extra speed for dx

    bool flagForPause = false; // flag for pause after failure
    bool flagDown = false; // ball not in window
    bool newGame = true; // for new game
    bool gameOver = false; // for game over

    int firstWins = 0; // number of wins first player
    int secondWins = 0; // number of wins first player

    int leftOrRight = 0; // 1 - right | 2 - left

    const sf::Color white = sf::Color::White; // white color

    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count(); // seed
    std::default_random_engine eng(seed);


    // font
    sf::Font font;
    font.loadFromFile("C:\\Users\\1\\CLionProjects\\game\\sansation.ttf");
    
    // text for score
    sf::Text textLeft;
    sf::Text textRight;
    setParametersTextScore(textLeft, white, font, 24, 350.f, 0.f);
    setParametersTextScore(textRight, white, font, 24, 430.f, 0.f);

    // text for win
    sf::Text winText;
    winText.setFont(font);
    winText.setCharacterSize(50);
    winText.setFillColor(white);
    winText.setPosition(310.f, 200.f);

    // text new game instructions
    sf::Text newGameInstructions;
    newGameInstructions.setFont(font);
    newGameInstructions.setCharacterSize(40);
    newGameInstructions.setFillColor(white);
    newGameInstructions.setPosition(240.f, 200.f);
    newGameInstructions.setString("start game - space");


    // text end game instructions
    sf::Text endGameInstructions;
    endGameInstructions.setFont(font);
    endGameInstructions.setCharacterSize(40);
    endGameInstructions.setFillColor(white);
    endGameInstructions.setPosition(240.f, 400.f);

    // ball create
    Ball ball(400.f, 300.f, 20.f);
    sf::CircleShape ballShape(0);
    ballShape.setFillColor(white);
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
            leftOrRight = 1;
            flagDown = true;
            extraSpeed = 0;
            dx = 0;
            dy = 0;
            ball.setX(400.f);
            ball.setY(300.f);
            std::cout << "Win left" << std::endl;
            firstWins++;
        }

        if (ball.getX() - ball.getR() < 0)
        {
            leftOrRight = 2;
            flagDown = true;
            extraSpeed = 0;
            dx = 0;
            dy = 0;
            ball.setX(400.f);
            ball.setY(300.f);
            std::cout << "Win right" << std::endl;
            secondWins++;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (flagDown || newGame) && !gameOver)
        {
            newGameInstructions.setString("");
            flagDown = false;
            if (eng()%2 && newGame) // for 1
            {
                newGame = false;
                dx = 6;
            }
            else if (!(eng()%2) && newGame) // for 0
            {    
                newGame = false;
                dx = -6;
            }
            if (leftOrRight == 1)
                dx = 6;
            if (leftOrRight == 2)
                dx = -6;
            dy = 2;
        }

        if (firstWins == 11)
        {
            winText.setString("Win left");
            gameOver = true;
            endGameInstructions.setString("restart game - F2");
        }

        if (secondWins == 11)
        {
            winText.setString("Win right");
            gameOver = true;
            endGameInstructions.setString("restart game - F2");
        }
        
        // ball move
        if(!flagForPause)
        {
    	    ball.setX(ball.getX()+dx);
    	    ball.setY(ball.getY()+dy);
        }
        
        // collision ball
        collisionBallY(dy, ball, HEIGHT);
        collisionBallXForLeft(dx, ball, firstPlayer, extraSpeed);
        collisionBallXForRight(dx, ball, secondPlayer, extraSpeed);


        // standard position for ball
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2) && gameOver)
        {   
            newGame = true;
            gameOver = false;
            newGameInstructions.setString("start game - space");
            endGameInstructions.setString("");
            winText.setString("");
            firstWins = 0;
            secondWins = 0;
            ball.setX(400.f);
            ball.setY(300.f);
        }

        // set position for ball shape
        ballShape.setPosition(ball.getX(), ball.getY());


        // first player control
        playerControll(firstPlayer, STEPSIZE, sf::Keyboard::W, sf::Keyboard::S);

        // set position for first player shape
        firstPlayerShape.setPosition(firstPlayer.getX(), firstPlayer.getY());


        // second player control
        playerControll(secondPlayer, STEPSIZE, sf::Keyboard::Up, sf::Keyboard::Down);

        // set position for second player shape
        secondPlayerShape.setPosition(secondPlayer.getX(), secondPlayer.getY());


        // draw field
        win.clear(sf::Color::Black);

        // draw text
        win.draw(textLeft);
        win.draw(textRight);
        win.draw(winText);
        win.draw(newGameInstructions);
        win.draw(endGameInstructions);

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