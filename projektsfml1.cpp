#include <SFML/Graphics.hpp>
#include "menu.h"
#include "game.h"
#include <fstream>
#include <iostream>

enum class meniuuu {
    Menu,
    Playing,
    Scores,
    Exiting,
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;

    meniuuu currentState = meniuuu::Menu;
    sf::Clock dtClock;

    sf::Font font;
    font.loadFromFile("arial.ttf");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                currentState = meniuuu::Exiting;

           
            if (currentState == meniuuu::Menu)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Up)
                        menu.przesunG();

                    else if (event.key.code == sf::Keyboard::Down)
                        menu.przesunD();

                    else if (event.key.code == sf::Keyboard::Enter)
                    {
                        int selected = menu.getSelectedItem();

                        
                        if (selected == 0)
                        {
                            game.reset();
                            currentState = meniuuu::Playing;
                        }

                       
                        else if (selected == 1) 
                        {
                            if (game.loadGame("zapis.txt"))   
                            {
                                std::cout << "Gra wczytana!\n";
                                currentState = meniuuu::Playing;
                            }
                            else
                            {
                                std::cout << "Blad wczytywania gry!\n";
                            }
                        }

                        
                        else if (selected == 2)
                        {
                            currentState = meniuuu::Scores;
                        }

                        
                        else if (selected == 3)
                        {
                            currentState = meniuuu::Exiting;
                        }
                    }
                }
            }

            
            else if (currentState == meniuuu::Playing)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        currentState = meniuuu::Menu;
                    }
                    
                    else if (event.key.code == sf::Keyboard::P)
                    {
                        game.captureGameState();
                        std::cout << "Stan gry zapisany!\n";
                    }
                }
            }

            
            else if (currentState == meniuuu::Scores)
            {
                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Enter)
                {
                    currentState = meniuuu::Menu;
                }
            }
        }

        
        sf::Time dt = dtClock.restart();

        if (currentState == meniuuu::Playing)
        {
            game.update(dt);

            if (game.isGameOver())
            {
                std::ofstream file("scores.txt", std::ios::app);
                if (file)
                    file << game.getHits() << "\n";

                game.setLastScore(game.getHits());

                currentState = meniuuu::Menu;
            }
        }
        else if (currentState == meniuuu::Exiting)
        {
            window.close();
        }

        
        window.clear();

        if (currentState == meniuuu::Menu)
        {
            menu.draw(window);
        }
        else if (currentState == meniuuu::Playing)
        {
            game.render(window);
        }
        else if (currentState == meniuuu::Scores)
        {
            int wynik = game.getLastScore();

            sf::Text text(
                "Ostatni wynik: " + std::to_string(wynik) +
                "\nWcisnij Enter",
                font, 28
            );

            text.setFillColor(sf::Color::White);

            sf::FloatRect b = text.getLocalBounds();
            text.setOrigin(b.width / 2, b.height / 2);
            text.setPosition(640 / 2.f, 480 / 2.f);

            window.draw(text);
        }

        window.display();
    }

    return 0;
}
