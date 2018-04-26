#ifndef SCAV_GAME_VIEW_HPP_
#define SCAV_GAME_VIEW_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Camera {
 private:
     View* camera;
 public:
     Camera();
     void set_center(Vector2f center);
     void draw(RenderWindow &window);
     ~Camera();
};




#endif  // SCAV_GAME_VIEW_HPP_
