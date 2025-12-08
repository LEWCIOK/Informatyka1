#include "menu.h"

Menu::Menu(float width, float height) {
    font.loadFromFile("arial.ttf");

    
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Cyan);
    menu[0].setString("Nowa gra");
    menu[0].setPosition({ width / 3, height / 5 });

    
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Wczytaj gre");
    menu[1].setPosition({ width / 3, height / 5 * 2 });

    
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Ostatnie wyniki");
    menu[2].setPosition({ width / 3, height / 5 * 3 });

    
    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Wyjscie");
    menu[3].setPosition({ width / 3, height / 5 * 4 });
}

void Menu::draw(sf::RenderWindow& window) {
    for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
        window.draw(menu[i]);
}

void Menu::przesunG() {
    menu[selectedItem].setFillColor(sf::Color::White);
    selectedItem = (selectedItem - 1 + MAX_LICZBA_POZIOMOW) % MAX_LICZBA_POZIOMOW;
    menu[selectedItem].setFillColor(sf::Color::Cyan);
}

void Menu::przesunD() {
    menu[selectedItem].setFillColor(sf::Color::White);
    selectedItem = (selectedItem + 1) % MAX_LICZBA_POZIOMOW;
    menu[selectedItem].setFillColor(sf::Color::Cyan);
}

int Menu::getSelectedItem() const {
    return selectedItem;
}
