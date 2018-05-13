#include "game_field.hpp"
#include <iostream>
#include <math.h>
GameField::GameField() : start(false), world(new b2World(b2Vec2(0, 0))), size(2000), pause(false) {
	borders[0] = new StaticObject(-1, world, b2Vec2(20, 2 * size), b2Vec2(-size, 0), 0);
	borders[1]  = new StaticObject(-2, world, b2Vec2(20, 2 * size), b2Vec2(size, 0), 0);
	borders[2]  = new StaticObject(-3, world, b2Vec2(2 * size, 20), b2Vec2(0, size), 0);
	borders[3]  = new StaticObject(-4, world, b2Vec2(2 * size, 20), b2Vec2(0, -size), 0);
}

void GameField::add_nickname(int cl_id, const std::string& nick) {
	nicknames.emplace(cl_id, nick);
}
std::string GameField::get_nickname(int cl_id) {
	auto f = nicknames.find(cl_id);
	if (f == nicknames.end()) {
		return std::string("stranger");
	}
	else {
		return f->second;
	}
}
GameField::~GameField() {
	reset();

	for (auto i = bullets.begin(); i != bullets.end();) {
		delete *i;
		i = bullets.erase(i);
	}

	for (auto i = objects.begin(); i != objects.end();) {
		delete i->second;
		i = objects.erase(i);
	}

	for (int i = 0; i < 4; ++i) {
		delete borders[i];
	}

	delete world;
}

void GameField::set_start(bool _s) {
	start = _s;
	if (_s) {
		start_time = std::clock();
	}
}

bool GameField::get_start() {
	return start;
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
void GameField::add_player(int cl_id, float x, float y) {
	auto f = nicknames.find(cl_id);
	Player* pl = nullptr;

	if (f != nicknames.end()) {
		pl = new Player(cl_id, world, b2Vec2(20 , 20), b2Vec2(x, y), f->second);
	} else {
		pl = new Player(cl_id, world, b2Vec2(20 , 20), b2Vec2(x, y), "stranger");
	}
	pl->set_hp(100);
	players.emplace(cl_id, pl);
}

b2World* GameField::get_world() {
	return world;
}

void GameField::delete_player(int cl_id) {
	Player* player = get_player(cl_id);
	players.erase(cl_id);
	delete player;
	nicknames.erase(cl_id);
}

PhysicsObject* GameField::get_object(int id) {
	auto i = objects.find(id);

	if (i != objects.end()) {
		return i->second;
	}
	return nullptr;
}

float GameField::get_size() {
	return size;
}

Player* GameField::get_player(int cl_id) {
	auto i = players.find(cl_id);

	if (i != players.end()) {
		return i->second;
	}
	return nullptr;
}

bool GameField::step() {
	static int last_step = 30;
	
	if (pause) {
		if (last_step == 0) {
			pause = false;
			state_packet << 52 << 0;
			return true;
		}
		last_step--;
		return false;
	}

	if (start) {
		for (auto i = objects_to_delete.begin(); i != objects_to_delete.end();) {
			delete *i;
			i = objects_to_delete.erase(i);
		}
		
		if (last_step == 0) {
			pause = false;
			std::clock_t end = std::clock();
			
			float secs = float(end - start_time) / CLOCKS_PER_SEC;
			int alive_count = 0;
			int winner;

			for (auto i = players.begin(); i != players.end(); ++i) {
				if (i->second->get_hp() > 0) {
					alive_count++;
					winner = i->first;
				}
			}

			if (alive_count < 2) {
				last_step = 200;
				pause = true;
				state_packet << 51 << winner;
				std::cout << "winner " << winner << std::endl;
				return false;
			}
			last_step = 30;
			float dead_zone = size - secs * 100;
			state_packet << 7 << 0 << dead_zone;

			for (auto i = players.begin(); i != players.end(); ++i) {
				const b2Vec2& pos = i->second->get_pos();

				if (abs(pos.x) > dead_zone || abs(pos.y) > dead_zone) {
					i->second->hit(10);
					state_packet << 5 << i->first << i->second->get_hp() ;
				}
			}
		}
		last_step--;
		world->Step(1.0f / 60.0f, 8, 3);
	}
	return false;
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

sf::Packet* GameField::get_objects(bool reset) {
	sf::Packet* res = new sf::Packet();
	
	if (reset) {
		*res << 104 << 0;
	}

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
			objects_to_delete.push_front(*i);
			bullets.erase(i);
			//delete b;
			return;
		}
	}
}

void GameField::restart() {
	start_time = std::clock();

	for (auto i = objects.begin(); i != objects.end();) {
		delete i->second;
		i = objects.erase(i);
	}

	for (auto i = bullets.begin(); i != bullets.end();) {
		delete *i;
		i = bullets.erase(i);
	}

	for (auto i = players.begin(); i != players.end();) {
		delete i->second;
		i = players.erase(i);
	}
	set_start(false);
}

void GameField::delete_object(int id) {
	auto i = objects.find(id);

	if (i != objects.end()) {
		state_packet << 103 << i->second->get_id();
		objects_to_delete.push_front(i->second);
		objects.erase(i);
	}
}