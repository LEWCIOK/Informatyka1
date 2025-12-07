#ifndef PALETKA_H
#define PALETKA_H
#include <SFML/Graphics.hpp>


class paletka {
private:
	float x, y;
	float szerokosc, wysokosc;
	float predkosc;
	sf::RectangleShape shape;


public:
	paletka(float startX, float startY, float szer, float wys, float pred);


	void moveLeft();
	void moveRight();
	void clampToBounds(float width);
	void draw(sf::RenderTarget& target);


	float getX() const { return x; }
	float getY() const { return y; }
	float getSzerokosc() const { return szerokosc; }
	float getWysokosc() const { return wysokosc; }
	sf::Vector2f getPosition() const {
		return sf::Vector2f(x, y);
	}

};


#endif