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


void DrawableObject::set_pos(Vector2f new_pos) {
    pos = new_pos;
}

void DrawableObject::draw(RenderWindow& window) {
}


void Player::set_pos(Vector2f new_pos) {
    pos = new_pos;
    b2Vec2 cur_pos = get_pos();
    b2Vec2 dpos = b2Vec2(new_pos.x, new_pos.y) - cur_pos;
    set_speed(20*dpos.x, 20*dpos.y);

    //skin->setPosition(pos);
}

/*void Player::set_position() {
    Vector2f curr_position = get_pos();
    skin->setPosition(curr_position);
}*/

void Player::mouse_rotation(RenderWindow& window) {
    Vector2i mouse_pos = sf::Mouse::getPosition(window);
    sf::Vector2f cursor =  window.mapPixelToCoords(mouse_pos);
    sf::Vector2f direction = cursor - skin->getPosition();
    player_rotation = std::atan2(direction.y, direction.x) * 180 / 3.14159265 + 90;
    skin->setRotation(player_rotation);
}

void Player::set_rotation(float new_rot) {
    player_rotation = new_rot;
    skin->setRotation(new_rot);
}

Player::Player(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos): DrawableObject(_id), KinematicObject(_world, size, pos) {}

void Player::set_player_sprite(Texture* player_texture) {
    skin = new Sprite(*player_texture);
    skin->setOrigin(skin->getLocalBounds().width / 2, skin->getLocalBounds().height / 2);
    skin->setScale(0.05, 0.05);
}

float Player::get_rotation() {
    return player_rotation;
}

void Player::draw(RenderWindow& window) {
	b2Vec2 p = get_pos();
	skin->setPosition(p.x, p.y);
    window.draw(*skin);
}


Player::~Player() {
    delete skin;
}

/*GameMap::GameMap(int _id, Texture map_texture): DrawableObject(_id) {
    map_sprite = new Sprite(map_texture);
}

GameMap::~GameMap() {
    delete map_sprite;
}*/

Wall::Wall(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos): DrawableObject(_id), StaticObject(_world, size, pos) {}

void Wall::set_pos(Vector2f new_pos) {
	(void) new_pos;
}

void Wall::set_sprite(Texture* player_texture) {
	wall_sprite = new Sprite(*player_texture);
    wall_sprite->setOrigin(wall_sprite->getLocalBounds().width / 2, wall_sprite->getLocalBounds().height / 2);
    wall_sprite->setScale(0.05, 0.05);
}

void Wall::draw(RenderWindow& window) {
	b2Vec2 p = get_pos();
	wall_sprite->setPosition(p.x, p.y);
    window.draw(*wall_sprite);
}

Wall::~Wall() {
	delete wall_sprite;
}

void Wall::set_rotation(float new_rot) {
	(void)new_rot;
}
DrawableBullet::DrawableBullet(b2World* _world, const b2Vec2& size,const b2Vec2& pos, const b2Vec2& speed, int _dmg) :
                DrawableObject(0), Bullet(_world, size, pos, speed, _dmg) {

}

DrawableBullet::~DrawableBullet() {
    delete bullet_sprite;
}

void DrawableBullet::set_rotation(float new_rot) {
    (void)new_rot;
}

void DrawableBullet::draw(RenderWindow &window) {
    b2Vec2 p = get_pos();
    bullet_sprite->setPosition(p.x, p.y);
    window.draw(*bullet_sprite);
}
void DrawableBullet::set_sprite(Texture* texture) {
    bullet_sprite = new Sprite(*texture);
    bullet_sprite->setOrigin(bullet_sprite->getLocalBounds().width / 2, bullet_sprite->getLocalBounds().height / 2);
    bullet_sprite->setScale(0.05, 0.05);
}