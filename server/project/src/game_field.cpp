#include "game_field.hpp"

GameField::GameField() {
}

GameField::~GameField() {
	reset();
	for (auto i = objects.begin(); i != objects.end(); ++i) {
		delete i->second;
	}
}

void GameField::add_object(PhysicsObject* obj) {
	int id = 0;
	if (objects.rbegin() != objects.rend()) {
		id = objects.rbegin()->first + 1;
	}
	objects.emplace(id, obj);
	obj->set_id(id);
}

void GameField::add_player(int cl_id) {
	Player* pl = new Player(cl_id);
	players.emplace(cl_id, pl);
	add_object(pl);
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