#include "GameState.h"
#include "paletka.h"
#include "pilka.h"
#include "Stone.h"
#include <fstream>
#include <string>

void GameState::capture(const paletka& paddle,
    const pilka& ball,
    const std::vector<Stone>& stones)
{
    
    paddlePosition = sf::Vector2f(paddle.getX(), paddle.getY());

    
    ballPosition = sf::Vector2f(ball.getX(), ball.getY());
    ballVelocity = sf::Vector2f(ball.getVx(), ball.getVy());

    
    blocks.clear();
    blocks.reserve(stones.size());

    for (const auto& st : stones) {
        if (st.isDestroyed() || st.getHP() <= 0)   
            continue;
        BlockData d;
        d.x = st.getPosition().x;
        d.y = st.getPosition().y;
        d.width = st.getSize().x;   
        d.height = st.getSize().y;
        d.hp = st.getHP();
        blocks.push_back(d);
    }
}


bool GameState::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
        return false;

    
    file << "PADDLE "
        << paddlePosition.x << " "
        << paddlePosition.y << "\n";

    
    file << "BALL "
        << ballPosition.x << " "
        << ballPosition.y << " "
        << ballVelocity.x << " "
        << ballVelocity.y << "\n";

    file << "BLOCKS_COUNT " << blocks.size() << "\n";

    
    for (const auto& b : blocks)
    {
        file << b.x << " "
            << b.y << " "
            << b.width << " "
            << b.height << " "
            << b.hp << "\n";
    }

    return true;
}

bool GameState::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return false;

    std::string tag;

    
    file >> tag;
    if (tag != "PADDLE") return false;
    file >> paddlePosition.x >> paddlePosition.y;

    
    file >> tag;
    if (tag != "BALL") return false;
    file >> ballPosition.x >> ballPosition.y
        >> ballVelocity.x >> ballVelocity.y;

    
    int count = 0;
    file >> tag;
    if (tag != "BLOCKS_COUNT") return false;
    file >> count;

    
    blocks.clear();
    blocks.reserve(count);

    for (int i = 0; i < count; i++)
    {
        BlockData d;
        file >> d.x >> d.y >> d.width >> d.height >> d.hp;
        blocks.push_back(d);
    }

    return true;
}

void GameState::apply(paletka& paddle,
    pilka& ball,
    std::vector<Stone>& stones) const
{

    
    paddle.setPosition(paddlePosition.x, paddlePosition.y);

    
    ball.setPosition(ballPosition.x, ballPosition.y);
    ball.setVelocity(ballVelocity.x, ballVelocity.y);

    
    stones.clear();
    stones.reserve(blocks.size());

    for (const auto& b : blocks)
    {
        stones.emplace_back(
            sf::Vector2f(b.x, b.y),
            sf::Vector2f(b.width, b.height), 
            b.hp

        );
        stones.back().aktualizujKolor();
    }
}
