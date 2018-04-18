#include "game_object.hpp"



GameObject::GameObject(int _id): id(_id) {};

int GameObject::get_id() {
    return id;
}



const Vector2f& DrawableObject::get_pos() const {
    return pos;
}

void Player::set_rotation(RenderWindow* window) {
    Vector2f playerCenter = skin->getPosition();
    Vector2f mousePosWindow = Vector2f(Mouse::getPosition(*window));
    Vector2f aimDir = mousePosWindow - playerCenter;//privet
    Vector2f aimDirNorm = aimDir / (float)(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
    float rotation = (atan2(aimDir.y, aimDir.x)) * 180 / 3.14159265 + 90;
}

Player::Player(int _id): DrawableObjec(int _id) {}

void Player::set_player_sprite(Texture player_texture) {
    skin = new Sprite(player_texture);
    skin->setOrigin(skin->getLocalBounds().width / 2, skin->getLocalBounds().height / 2);
    skin->setScale(0.05, 0.05);
}

float Player::get_rotation() {
    return rotation;
}

void Player::draw(RenderWindow* window) {
    window->draw(*skin);
}

GameMap::GameMap(Texture map_texture) {
    map_sprite = new Sprite(map_texture);

}
