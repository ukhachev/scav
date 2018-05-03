#include "game_field.hpp"
#include <iostream>
GameField::GameField() : world(new b2World(b2Vec2(0, 0))) {
	StaticObject* left = new StaticObject(-1, world, b2Vec2(10, 1000), b2Vec2(-500, 0));
	StaticObject* right = new StaticObject(-2, world, b2Vec2(10, 1000), b2Vec2(500, 0));
	StaticObject* top = new StaticObject(-3, world, b2Vec2(1000, 10), b2Vec2(0, 500));
	StaticObject* bot = new StaticObject(-4, world, b2Vec2(1000, 10), b2Vec2(0, -500));
	(void)left;
	(void)top;
	(void)bot;
	(void)right;
}

GameField::~GameField() {
	reset();
	for (auto i = objects.begin(); i != objects.end(); ++i) {
		delete i->second;
	}
}

void GameField::add_object(PhysicsObject* obj) {
	int id = 200;
	if (objects.rbegin() != objects.rend()) {
		id = objects.rbegin()->first + 1;
	}
	objects.emplace(id, obj);
	obj->set_id(id);
}

void GameField::add_bullet(Bullet* bullet) {
	bullets.push_front(bullet);
}
void GameField::add_player(int cl_id) {
	Player* pl = new Player(cl_id, world, b2Vec2(20 , 20), b2Vec2(0, 0));
	players.emplace(cl_id, pl);
}

b2World* GameField::get_world() {
	return world;
}

void GameField::delete_player(int cl_id) {
	Player* player = get_player(cl_id);
	players.erase(cl_id);
	objects.erase(player->get_id());
	delete player;
}

PhysicsObject* GameField::get_object(int id) {
	auto i = objects.find(id);

	if (i != objects.end()) {
		return i->second;
	}
	return nullptr;
}

Player* GameField::get_player(int cl_id) {
	auto i = players.find(cl_id);

	if (i != players.end()) {
		return i->second;
	}
	return nullptr;
}

void GameField::step() {
	world->Step(1.0f / 60.0f, 8, 3);
}

sf::Packet* GameField::get_state_packet() {

	return &state_packet;
}

void GameField::reset() {
	for (auto i = private_packets.begin(); i != private_packets.end(); ++i) {
		delete i->second;
	}
	private_packets.clear();
	state_packet.clear();
}

sf::Packet* GameField::add_private_packet(int cl_id) {
	auto i = private_packets.find(cl_id);
	if (i == private_packets.end()) {
		sf::Packet* p = new sf::Packet();
		private_packets.emplace(cl_id, p);
		return p;
	}
	return i->second;
}

std::map<int, sf::Packet*>::iterator GameField::p_packets_begin() {
	return private_packets.begin();
}

std::map<int, sf::Packet*>::iterator GameField::p_packets_end() {
	return private_packets.end();
}

sf::Packet* GameField::get_objects() {
	sf::Packet* res = new sf::Packet();
	for (auto i = objects.begin(); i != objects.end(); ++i) {
		b2Vec2 pos = i->second->get_pos();
		*res << 2 << i->first << i->second->object_type() << pos.x << pos.y << i->second->texture();
	}
	return res;
}

b2World* GameField::get_physics_world() {
	return world;
}

void GameField::delete_bullet(Bullet* b) {
	for (auto i = bullets.begin(); i != bullets.end(); ++i) {
		if (*i == b) {
			bullets.erase(i);
			delete b;
			return;
		}
	}
}

void GameField::delete_object(int id) {
	auto i = objects.find(id);
	//std::cout << "abc" << std::endl;
	if (i != objects.end()) {
		delete i->second;
		objects.erase(i);
	}
}