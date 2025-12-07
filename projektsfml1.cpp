#include <SFML/Graphics.hpp>
#include "menu.h"
#include "game.h"

enum class GameState {
    Menu,
    Playing,
    Scores,
    Exiting
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;

    GameState currentState = GameState::Menu;
    sf::Clock dtClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                currentState = GameState::Exiting;

            // ================= MENU =================
            if (currentState == GameState::Menu)
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

                        if (selected == 0)              // NOWA GRA
                        {
                            game.reset();               // 🔥 Restart gry
                            currentState = GameState::Playing;
                        }
                        else if (selected == 1)         // WYNIKI
                        {
                            currentState = GameState::Scores;
                        }
                        else if (selected == 2)         // WYJŚCIE
                        {
                            currentState = GameState::Exiting;
                        }
                    }
                }
            }

            // ================ GRA ===================
            else if (currentState == GameState::Playing)
            {
                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape)
                {
                    currentState = GameState::Menu;
                }
            }

            // ============= WYNIKI ===================
            else if (currentState == GameState::Scores)
            {
                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Enter)
                {
                    currentState = GameState::Menu;
                }
            }
        }

        // ============================================
        //                 UPDATE
        // ============================================
        sf::Time dt = dtClock.restart();

        if (currentState == GameState::Playing)
        {
            game.update(dt);

            if (game.isGameOver())
                currentState = GameState::Scores;
        }
        else if (currentState == GameState::Exiting)
        {
            window.close();
        }

        // ============================================
        //                 RENDER
        // ============================================
        window.clear();

        if (currentState == GameState::Menu)
        {
            menu.draw(window);
        }
        else if (currentState == GameState::Playing)
        {
            game.render(window);
        }
        else if (currentState == GameState::Scores)
        {
            sf::Font font;
            font.loadFromFile("C:\\Users\\macie\\source\\repos\\projektsfml1\\x64\\Release\\Arial.ttf");

            sf::Text text("KONIEC GRY - wcisnij Enter", font, 28);
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
