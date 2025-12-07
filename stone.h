#ifndef STONE_H
#define STONE_H
#include <SFML/Graphics.hpp>
#include <array>


class Stone : public sf::RectangleShape {
private:
	int m_punktyZycia;
	bool m_jestZniszczony;
	static const std::array<sf::Color, 4> m_colorLUT;
	

public:
	Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L);

	int getHP() const {
		return m_punktyZycia;}

	void trafienie();
	void aktualizujKolor();
	bool isDestroyed() const { return m_jestZniszczony; }
	void draw(sf::RenderTarget& target) const;
};
#endif