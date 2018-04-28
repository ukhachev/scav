
#include "view.hpp"


void Camera::set_center(Vector2f center) {
    camera->setCenter(center);
}

void Camera::draw(RenderWindow &window) {
    window.setView(camera);
}
