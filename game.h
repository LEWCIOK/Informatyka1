#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "stone.h"
#include "paletka.h"
#include "pilka.h"

class Game
{
public:
    Game();

    void update(sf::Time dt);
    void render(sf::RenderTarget& target);
    void reset();
    
    bool isGameOver() const { return m_gameOver; }
    int getHits() const { return m_hits; }
    int getLastScore() const { return m_lastScore; }
    void setLastScore(int s) { m_lastScore = s; }

    template<typename T>
    T clampValue(T value, T minv, T maxv) {
        return (value < minv) ? minv : (value > maxv ? maxv : value);
    }

private:
    paletka m_paletka;
    pilka m_pilka;

    std::vector<Stone> m_bloki;

    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;

    int m_frame = 0;
    bool m_gameOver = false;   // <-- DODANE
    int m_hits = 0;
    int m_lastScore = 0;
};


#endif
