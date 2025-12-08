#include "game.h"
#include <iostream>
#include "GameState.h"
#include <fstream>
#include <string>

Game::Game()
    : m_paletka(320.f, 440.f, 100.f, 20.f, 8.f),
    m_pilka(320.f, 300.f, 4.f, 1.f, 4.f)
{
   
    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float PRZERWA = 2.f;
    const float OFFSET_Y = 50.f;

    const float ROZMIAR_BLOKU_X =
        (WIDTH - (ILOSC_KOLUMN - 1) * PRZERWA) / ILOSC_KOLUMN;

    for (int y = 0; y < ILOSC_WIERSZY; ++y) {
        for (int x = 0; x < ILOSC_KOLUMN; ++x) {

            float posX = x * (ROZMIAR_BLOKU_X + PRZERWA);
            float posY = OFFSET_Y + y * (ROZMIAR_BLOKU_Y + PRZERWA);

            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;

            m_bloki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                L
            );
        }
    }
}

void Game::update(sf::Time dt)
{
    m_paletka.clampToBounds(WIDTH);

    m_pilka.move();
    m_pilka.collideWalls(WIDTH, HEIGHT);

    if (m_pilka.collidePaddle(m_paletka)) {
        std::cout << "HIT PADDLE\n";
        m_hits++;
    }

    
    for (auto& b : m_bloki) {
        if (b.isDestroyed()) continue;

        float bx = b.getPosition().x;
        float by = b.getPosition().y;
        float bw = b.getSize().x;
        float bh = b.getSize().y;

        float closestX = clampValue(m_pilka.getX(), bx, bx + bw);
        float closestY = clampValue(m_pilka.getY(), by, by + bh);

        float dx = m_pilka.getX() - closestX;
        float dy = m_pilka.getY() - closestY;
        float dist2 = dx * dx + dy * dy;
        float r = m_pilka.getRadius();

        if (dist2 <= r * r) {
            m_pilka.bounceY();
            b.trafienie();
        }
    }

    
    if (m_pilka.getY() - m_pilka.getRadius() > HEIGHT) {
        std::cout << "MISS! KONIEC GRY\n";
        m_lastScore = m_hits;
        m_gameOver = true;
    }

    if (m_frame % 30 == 0) {
        std::cout << "x=" << m_pilka.getX()
            << " y=" << m_pilka.getY()
            << " vx=" << m_pilka.getVx()
            << " vy=" << m_pilka.getVy()
            << std::endl;
    }
    m_frame++;
}

void Game::render(sf::RenderTarget& target)
{
    m_paletka.draw(target);
    m_pilka.draw(target);

    for (auto& b : m_bloki)
        b.draw(target);
}

void Game::reset()
{
    
    m_paletka = paletka(320.f, 440.f, 100.f, 20.f, 8.f);

    
    m_pilka = pilka(320.f, 300.f, 4.f, 1.f, 4.f);

    
    m_bloki.clear();

    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float PRZERWA = 2.f;
    const float OFFSET_Y = 50.f;

    const float ROZMIAR_BLOKU_X =
        (WIDTH - (ILOSC_KOLUMN - 1) * PRZERWA) / ILOSC_KOLUMN;

    for (int y = 0; y < ILOSC_WIERSZY; ++y) {
        for (int x = 0; x < ILOSC_KOLUMN; ++x) {

            float posX = x * (ROZMIAR_BLOKU_X + PRZERWA);
            float posY = OFFSET_Y + y * (ROZMIAR_BLOKU_Y + PRZERWA);

            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;

            m_bloki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                L
            );
        }
    }

    m_gameOver = false;
    m_frame = 0;
    m_hits = 0;
}


void Game::captureGameState()
{
    GameState gs;

  
    gs.capture(m_paletka, m_pilka, m_bloki);

  
    if (gs.saveToFile("zapis.txt"))
        std::cout << "[Game] Stan gry zapisany do zapis.txt\n";
    else
        std::cout << "[Game] ❌ Błąd zapisu stanu gry!\n";
}
void Game::loadSavedGame()
{
    GameState gs;

    if (!gs.loadFromFile("zapis.txt"))
    {
        std::cout << "❌ Blad: nie mozna wczytac zapis.txt\n";
        return;
    }

    gs.apply(m_paletka, m_pilka, m_bloki);

    std::cout << "✔ Stan gry wczytany!\n";
}
bool Game::loadGame(const std::string& filename)
{
    if (!m_savedState.loadFromFile(filename))
        return false;

    m_savedState.apply(m_paletka, m_pilka, m_bloki);

    m_gameOver = false;
    m_hits = 0;
    m_frame = 0;

    std::cout << "[Game] Gra została wczytana.\n";
    return true;
}



