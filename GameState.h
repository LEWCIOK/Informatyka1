#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


struct BlockData {
    float x, y;
    float width, height;
    int hp;
};


class paletka;
class pilka;
class Stone;


class GameState {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:
    GameState() = default;
    bool loadFromFile(const std::string& filename);
    void apply(paletka& paddle, pilka& ball, std::vector<Stone>& stones) const;

    void capture(const paletka& paddle,
        const pilka& ball,
        const std::vector<Stone>& stones);

    
    bool saveToFile(const std::string& filename) const;

   
    const sf::Vector2f& getPaddlePos() const { return paddlePosition; }
    const sf::Vector2f& getBallPos() const { return ballPosition; }
    const sf::Vector2f& getBallVel() const { return ballVelocity; }
    const std::vector<BlockData>& getBlocks() const { return blocks; }
};

#endif
