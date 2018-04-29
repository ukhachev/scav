#include "game_object.hpp"

//GameObject
GameObject::GameObject() {
}

GameObject::~GameObject() {
}

void GameObject::set_id(int _id) {
	id = _id;
}

int GameObject::get_id() {
	return id;
}

//Player
Player::Player(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos) 
				: StaticObject(_id, _world, size, pos) {
}

Player::~Player() {
}