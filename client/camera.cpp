
#include "camera.hpp"




Camera::Camera() {}

void Camera::set_center(Player* player) {
    //camera.setSize(1920, 1080);
    camera.setCenter(player->get_pos().x, player->get_pos().y);
}

void Camera::draw(RenderWindow& window) {
    window.setView(camera);
}
