#include "pilka.h"
#include <cmath>
#include <algorithm>

pilka::pilka(float startX, float startY, float r, float velX, float velY)
    : x(startX), y(startY), radius(r), vx(velX), vy(velY)
{
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
}

void pilka::move()
{
    x += vx;
    y += vy;
    shape.setPosition(x, y);
}

void pilka::bounceX() { vx = -vx; }
void pilka::bounceY() { vy = -vy; }

void pilka::collideWalls(float width, float height)
{
    if (x - radius <= 0.f) { x = radius; bounceX(); }
    else if (x + radius >= width) { x = width - radius; bounceX(); }

    if (y - radius <= 0.f) { y = radius; bounceY(); }

    shape.setPosition(x, y);
}

bool pilka::collidePaddle(const paletka& p)
{
    float px = p.getX();
    float py = p.getY();
    float pw = p.getSzerokosc();
    float ph = p.getWysokosc();

    float halfW = pw / 2.f;
    float halfH = ph / 2.f;

    float closestX = std::max(px - halfW, std::min(x, px + halfW));
    float closestY = std::max(py - halfH, std::min(y, py + halfH));

    float dx = x - closestX;
    float dy = y - closestY;

    if (dx * dx + dy * dy <= radius * radius)
    {
        vy = -std::abs(vy);
        y = (py - halfH) - radius;

        // zachowanie ogólnej prêdkoœci
        float speed = std::sqrt(vx * vx + vy * vy);

        // odbicie zale¿ne od miejsca trafienia
        float relativeHit = (x - px) / halfW;
        vx = relativeHit * speed;

        shape.setPosition(x, y);
        return true;
    }

    return false;
}

void pilka::draw(sf::RenderTarget& target)
{
    target.draw(shape);
}
