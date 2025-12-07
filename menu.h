#pragma once
#include <SFML/Graphics.hpp>

#define MAX_LICZBA_POZIOMOW 3

class Menu {
private:
    sf::Font font;
    sf::Text menu[MAX_LICZBA_POZIOMOW];
    int selectedItem = 0;

public:
    Menu(float w, float h);
    void przesunG();
    void przesunD();
    int getSelectedItem() const;
    void draw(sf::RenderWindow& window);
};
