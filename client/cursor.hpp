#ifndef SCAV_CURSOR_HPP_
#define SCAV_CURSOR_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "game_object.hpp"


using namespace sf;

class Cursor {
 private:
     Sprite* cursor;
 public:
     Cursor(Texture* cursor_texture);
     //void set_pos(RenderWindow& window);
     void draw(RenderWindow& window);
    // Vector2f get_pos();
     ~Cursor();
};


#endif  // SCAV_CURSOR_HPP_
