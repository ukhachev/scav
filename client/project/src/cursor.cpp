

#include "cursor.hpp"

Cursor::Cursor(Texture* cursor_texture) {
    cursor = new Sprite(*cursor_texture);
    cursor->setOrigin(cursor->getLocalBounds().width / 2, cursor->getLocalBounds().height / 2);
    cursor->setScale(0.1, 0.1);
}


void Cursor::draw(RenderWindow& window) {
    sf::Vector2f cursor_pos =  window.mapPixelToCoords(Mouse::getPosition(window));
    cursor->setPosition(cursor_pos);
    window.draw(*cursor);
}


Cursor::~Cursor() {
    delete cursor;
}
