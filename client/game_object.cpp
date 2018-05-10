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

void DrawableObject::get_delete_sprite(TempContainer& tmp_a_cont) {}

void DrawableObject::hit() {

}

void Player::set_pos(Vector2f new_pos) {
    pos = new_pos;
    b2Vec2 cur_pos = get_pos();
    b2Vec2 dpos = b2Vec2(new_pos.x, new_pos.y) - cur_pos;
    set_speed(20*dpos.x, 20*dpos.y);
}

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
    dead->setRotation(new_rot);
}

void Player::set_ammo(int val) {
    ammo = val;
}

int Player::get_ammo() {
    return ammo;
}

Player::Player(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos):
        DrawableObject(_id), KinematicObject(_world, size, pos), timer(0), ammo(50) {}

void Player::set_player_sprite(Texture* player_texture) {
    skin = new Sprite(*player_texture);
    skin->setOrigin(skin->getLocalBounds().width / 2, skin->getLocalBounds().height / 2);
    skin->setScale(0.05, 0.05);
}

void Player::set_damage_sprite(Texture* damage_texture) {
    damage = new Sprite(*damage_texture);
    damage->setOrigin(damage->getLocalBounds().width / 2, damage->getLocalBounds().height / 2);
    damage->setScale(1.5, 1.5);
}

void Player::set_dead_sprite(Texture* dead_texture) {
    dead = new Sprite(*dead_texture);
    dead->setOrigin(dead->getLocalBounds().width / 2, dead->getLocalBounds().height / 2);
    dead->setScale(1.5, 1.5);
}

void Player::get_delete_sprite(TempContainer& tmp_a_cont) {
    dead->setPosition(skin->getPosition());
    TempObject* tmp_obj = new TempObject(dead, 100);
    tmp_a_cont.add(tmp_obj);
}


float Player::get_rotation() {
    return player_rotation;
}

void Player::draw(RenderWindow& window) {
    b2Vec2 p = get_pos();
    if (hp > 0) {
        skin->setPosition(p.x, p.y);
        window.draw(*skin);
    } else {
        dead->setPosition(p.x, p.y);
        window.draw(*dead);
    }
    if (timer != 0) {
        damage->setPosition(p.x, p.y);
        window.draw(*damage);
        timer--;
    }
}

void Player::hit() {
    timer = 4;
}


Player::~Player() {
    delete skin;
    delete damage;
    delete dead;
}


Wall::Wall(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos): DrawableObject(_id), StaticObject(_world, size, pos), timer(0) {}

void Wall::set_pos(Vector2f new_pos) {
	(void) new_pos;
}

void Wall::set_sprite(Texture* player_texture) {
	wall_sprite = new Sprite(*player_texture);
    wall_sprite->setOrigin(wall_sprite->getLocalBounds().width / 2, wall_sprite->getLocalBounds().height / 2);
    wall_sprite->setScale(0.05, 0.05);
}

void Wall::set_damage_sprite(Texture* damage_texture) {
    damage = new Sprite(*damage_texture);
    damage->setOrigin(damage->getLocalBounds().width / 2, damage->getLocalBounds().height / 2);
    damage->setScale(1.5, 1.5);
}

void Wall::hit() {
    timer = 4;
}

void Wall::draw(RenderWindow& window) {
	b2Vec2 p = get_pos();
	wall_sprite->setPosition(p.x, p.y);
    window.draw(*wall_sprite);
    if (timer != 0) {
        damage->setPosition(p.x, p.y);
        window.draw(*damage);
        timer--;
    }

}

Wall::~Wall() {
	delete wall_sprite;
    delete damage;
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

AidKit::AidKit(int _id): DrawableObject(_id), dead(nullptr) {

}

AidKit::~AidKit() {
    delete sprite;
}

void AidKit::set_pos(sf::Vector2f new_pos) {
    sprite->setPosition(new_pos.x, new_pos.y);
}

void AidKit::set_sprite(Texture* texture) {
    sprite = new Sprite(*texture);
    sprite->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2);
    sprite->setScale(1.5, 1.5);
}

/*void AidKit::set_dead_sprite(Texture* texture) {
    dead = new Sprite(*texture);
    dead->setOrigin(dead->getLocalBounds().width / 2, dead->getLocalBounds().height / 2);
    dead->setScale(1.5, 1.5);
}*/

void AidKit::set_dead_animation(AnimationObject* a_obj) {
    std::cout << "Animation added to object" << std::endl;
    dead = new AnimationObject(a_obj);
}

void AidKit::get_delete_sprite(TempContainer& tmp_a_cont) {
    if (dead!=nullptr) {
        dead->set_position(sprite->getPosition());
        //dead->setPosition(sprite->getPosition());
        //TempObject* tmp_obj = new TempObject(dead, 4);
        //tmp_a_cont.add(tmp_obj);
        tmp_a_cont.add(dead);
    }
}

void AidKit::draw(RenderWindow& window) {
    window.draw(*sprite);
}

void AidKit::set_rotation(float new_rot) {
    (void) new_rot;
}
