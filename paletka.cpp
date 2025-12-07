#include "paletka.h"


paletka::paletka(float startX, float startY, float szer, float wys, float pred)
	: x(startX), y(startY), szerokosc(szer), wysokosc(wys), predkosc(pred) {
	shape.setSize({ szerokosc, wysokosc });
	shape.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::Red);
}


void paletka::moveLeft() {
	x -= predkosc;
	shape.setPosition(x, y);
}


void paletka::moveRight() {
	x += predkosc;
	shape.setPosition(x, y);
}


void paletka::clampToBounds(float width) {
	if (x - szerokosc / 2 < 0) x = szerokosc / 2;
	if (x + szerokosc / 2 > width) x = width - szerokosc / 2;


	shape.setPosition(x, y);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		moveLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		moveRight();
}


void paletka::draw(sf::RenderTarget& target) {
	target.draw(shape);
}

