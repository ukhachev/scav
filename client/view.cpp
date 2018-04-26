
#include "view.hpp"


Camera::Camera() {
    //camera = new View();
};

void Camera::set_center(Vector2f center) {
    camera->setCenter(center);
}

void Camera::draw(RenderWindow &window) {
    window.setView(*camera);
}


Camera::~Camera() {
    //delete camera;
}
