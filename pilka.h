#ifndef PILKA_H
#define PILKA_H
#include <SFML/Graphics.hpp>
#include "paletka.h"


class pilka {
private:
	float x, y;
	float vx, vy;
	float radius;
	sf::CircleShape shape;


public:
	pilka(float startX, float startY, float r, float velX, float velY);
	void move();
	void bounceX();
	void bounceY();
	void collideWalls(float width, float height);
	bool collidePaddle(const paletka& p);
	void draw(sf::RenderTarget& target);


	float getX() const { return x; }
	float getY() const { return y; }
	float getVx() const { return vx; }
	float getVy() const { return vy; }
	float getRadius() const { return radius; }
	sf::Vector2f getPosition() const {
		return sf::Vector2f(x, y);
	}

	sf::Vector2f getVelocity() const {
		return sf::Vector2f(vx, vy);
	}

};


#endif