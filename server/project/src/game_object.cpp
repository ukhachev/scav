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

//Physics object
PhysicsObject::PhysicsObject() {
}

PhysicsObject::~PhysicsObject() {
}

void PhysicsObject::set_position(float _x, float _y, float _angle) {
	pos.x = _x;
	pos.y = _y;
	pos.angle = _angle;
}

const Position& PhysicsObject::get_pos() {
	return pos;
}

//Player
Player::Player(int _cl_id) : cl_id(_cl_id) {
}

Player::~Player() {
}

int Player::get_client() {
	return cl_id;
}