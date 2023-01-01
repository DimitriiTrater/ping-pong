#include <iostream>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[])
{
    const int W = 800;
    const int H = 600;

    float x1 = W/4;
    float y1 = H/2;
    float x2 = W/4*3;
    float y2 = H/2;
    float r1 = 50;
    float r2 = 50;

    sf::RenderWindow win(sf::VideoMode(W, H), "Game");
    
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(500.f, 50.f);

    sf::RectangleShape first_player(sf:: Vector2f(20.f, 200.f));
    first_player.setPosition(10.f, 10.f);

    sf::RectangleShape second_player(sf:: Vector2f(20.f, 200.f));
    second_player.setPosition(740.f, 10.f);

    win.setFramerateLimit(60);
    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                win.close();
                std::cout << "log: win closed" << std::endl;
            }

            if (event.type == sf::Event::LostFocus)
                std::cout << "log: lost focus" << std::endl;

            if (event.type == sf::Event::GainedFocus)
                std::cout << "log: gained focus" << std::endl;
        }

        win.clear(sf::Color::Black);

        win.draw(first_player);
        win.draw(second_player);
        win.draw(ball);    

        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            first_player.move(0.f, -3.f);
            //std::cout << "log: pressed W" << std::endl;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            first_player.move(0.f, 3.f);
            //std::cout << "log: pressed S" << std::endl;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            second_player.move(0.f, -3.f);
            //std::cout << "log: pressed Up" << std::endl;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            second_player.move(0.f, 3.f);
            //std::cout << "log: pressed Down" << std::endl;
        }

        win.display();



    }
    return 0;
}