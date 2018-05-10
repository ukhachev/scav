#include "game_field.hpp"
#include <iostream>
GameField::GameField() : world(new b2World(b2Vec2(0, 0))) {
	borders[0] = new StaticObject(-1, world, b2Vec2(10, 2000), b2Vec2(-1000, 0), 0);
	borders[1]  = new StaticObject(-2, world, b2Vec2(10, 2000), b2Vec2(1000, 0), 0);
	borders[2]  = new StaticObject(-3, world, b2Vec2(2000, 10), b2Vec2(0, 1000), 0);
	borders[3]  = new StaticObject(-4, world, b2Vec2(2000, 10), b2Vec2(0, -1000), 0);
	start_time = std::clock();
}

GameField::~GameField() {
	reset();
	for (auto i = objects.begin(); i != objects.end(); ++i) {
		delete i->second;
		objects.erase(i);
	}
	for (auto i = bullets.begin(); i != bullets.end(); ++i) {
		delete *i;
		bullets.erase(i);
	}
	for (int i = 0; i < 4; ++i) {
		delete borders[i];
	}
	delete world;
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
	Player* pl = new Player(cl_id, world, b2Vec2(20 , 20), b2Vec2(0, 0), "stranger");
	players.emplace(cl_id, pl);
}

b2World* GameField::get_world() {
	return world;
}

void GameField::delete_player(int cl_id) {
	Player* player = get_player(cl_id);
	players.erase(cl_id);
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
	std::clock_t end = std::clock();
	float secs = float(end - start_time) / CLOCKS_PER_SEC;
	
	borders[0]->set_pos(-1000 + secs*500, 0);
	borders[1]->set_pos(1000 - secs*500, 0);
	borders[2]->set_pos(0, 1000 + secs*500);
	borders[3]->set_pos(0, -1000 + secs*500);
	
	state_packet << 7 << 0 << secs;

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
	*res << 7 << 1 << borders[1]->get_pos().x;
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

void GameField::restart() {
	start_time = std::clock();
	state_packet << 104 << 0;
	for (auto i = objects.begin(); i != objects.end();) {
		delete i->second;
		i = objects.erase(i);
	}

	for (auto i = bullets.begin(); i != bullets.end();) {
		delete *i;
		i = bullets.erase(i);
	}

	for (auto i = players.begin(); i != players.end(); ++i) {
		i->second->set_hp(100);
	}
}

void GameField::delete_object(int id) {
	auto i = objects.find(id);

	if (i != objects.end()) {
		state_packet << 103 << i->second->get_id();
		delete i->second;
		objects.erase(i);
	}
}