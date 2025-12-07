#include "Stone.h"


const std::array<sf::Color, 4> Stone::m_colorLUT = {
sf::Color::Transparent,
sf::Color::Red,
sf::Color::Yellow,
sf::Color::Blue
};


Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L) {
	m_punktyZycia = L;
	m_jestZniszczony = false;
	setSize(rozmiar);
	setPosition(startPos);
	setOutlineThickness(2.f);
	aktualizujKolor();
}


void Stone::trafienie() {
	if (m_jestZniszczony) return;
	--m_punktyZycia;
	aktualizujKolor();
	if (m_punktyZycia <= 0) m_jestZniszczony = true;
}


void Stone::aktualizujKolor() {
	if (m_punktyZycia < 0)
		setFillColor(m_colorLUT[0]);
	else if (m_punktyZycia >= (int)m_colorLUT.size())
		setFillColor(m_colorLUT.back());
	else
		setFillColor(m_colorLUT[m_punktyZycia]);
}


void Stone::draw(sf::RenderTarget& target) const {
	if (!m_jestZniszczony)
		target.draw(*this);
}