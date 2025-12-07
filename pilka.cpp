#include "pilka.h"
#include <cmath>


pilka::pilka(float startX, float startY, float r, float velX, float velY)
	: x(startX), y(startY), radius(r), vx(velX), vy(velY) {
	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::White);
}


void pilka::move() {
	x += vx;
	y += vy;
	shape.setPosition(x, y);
}


void pilka::bounceX() { vx = -vx; }
void pilka::bounceY() { vy = -vy; }


void pilka::collideWalls(float width, float height) {
	if (x - radius <= 0.f) { x = radius; bounceX(); }
	else if (x + radius >= width) { x = width - radius; bounceX(); }
	if (y - radius <= 0.f) { y = radius; bounceY(); }
	shape.setPosition(x, y);
}


bool pilka::collidePaddle(const paletka& p) {
	float palX = p.getX();
	float palY = p.getY();
	float palW = p.getSzerokosc();
	float palH = p.getWysokosc();


	bool wZakresieX = (x >= palX - palW / 2.f && x <= palX + palW / 2.f);
	bool dotykaZGory = (y + radius >= palY - palH / 2.f) && (y - radius < palY - palH / 2.f);


	if (wZakresieX && dotykaZGory) {
		vy = -std::abs(vy);
		y = (palY - palH / 2.f) - radius;
		shape.setPosition(x, y);
		return true;
	}
	return false;
}


void pilka::draw(sf::RenderTarget& target) { target.draw(shape); }