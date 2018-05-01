#ifndef SCAV_CAMERA_HPP_
#define SCAV_CAMERA_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "game_object.hpp"

using namespace sf;

class Camera {
 private:
     View camera;
 public:
     Camera();
     void set_center(Player* player);
     void draw(RenderWindow& window);
};


#endif //  SCAV_CAMERA_HPP_
