#include "game_object.hpp"
#include "gamefield.hpp"
#include <math.h>
#include <iostream>


GameObject::GameObject(int _id): id(_id) {};

int GameObject::get_id() {
    return id;
}

DrawableObject::DrawableObject(int _id): GameObject(_id) {}
DrawableObject::~DrawableObject() {}


const Vector2f& DrawableObject::get_pos() const {
    return pos;
}

void DrawableObject::set_pos(Vector2f new_pos) {
    pos = new_pos;
}

void DrawableObject::draw(RenderWindow& window) {
}


void Player::set_pos(Vector2f new_pos) {
    pos = new_pos;
    skin->setPosition(pos);
}

/*void Player::set_position() {
    Vector2f curr_position = get_pos();
    skin->setPosition(curr_position);
}*/

void Player::mouse_rotation(RenderWindow& window) {
    Vector2f playerCenter = skin->getPosition();
    Vector2f mousePosWindow = Vector2f(Mouse::getPosition(window));
    Vector2f aimDir = mousePosWindow - playerCenter;
    Vector2f aimDirNorm = aimDir / (float)(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
    player_rotation = (atan2(aimDir.y, aimDir.x)) * 180 / 3.14159265 +90;
    skin->setRotation(player_rotation);
}

void Player::set_rotation(float new_rot) {
    player_rotation = new_rot;
    skin->setRotation(new_rot);
}

Player::Player(int _id): DrawableObject(_id) {}

void Player::set_player_sprite(Texture* player_texture) {
    skin = new Sprite(*player_texture);
    skin->setOrigin(skin->getLocalBounds().width / 2, skin->getLocalBounds().height / 2);
    skin->setScale(0.05, 0.05);
}

float Player::get_rotation() {
    return player_rotation;
}

void Player::draw(RenderWindow& window) {
    window.draw(*skin);
}

Player::~Player() {
    delete skin;
}

GameMap::GameMap(int _id, Texture map_texture): DrawableObject(_id) {
    map_sprite = new Sprite(map_texture);
}

GameMap::~GameMap() {
    delete map_sprite;
}
