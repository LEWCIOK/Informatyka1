#include "GameState.h"
#include "paletka.h"
#include "pilka.h"
#include "Stone.h"

void GameState::capture(const paletka& paddle,
    const pilka& ball,
    const std::vector<Stone>& stones)
{
    // ===== Paletka =====
    paddlePosition = sf::Vector2f(paddle.getX(), paddle.getY());

    // ===== Pi�ka =====
    ballPosition = sf::Vector2f(ball.getX(), ball.getY());
    ballVelocity = sf::Vector2f(ball.getVx(), ball.getVy());

    // ===== Bloki =====
    blocks.clear();
    blocks.reserve(stones.size());

    for (const auto& st : stones) {
        BlockData d;
        d.x = st.getPosition().x;
        d.y = st.getPosition().y;
        d.width = st.getSize().x;
        d.height = st.getSize().y;
        d.hp = st.getHP();
        blocks.push_back(d);
    }
}