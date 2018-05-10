#ifndef SCAV_SERVER_GAME_FIELD_HPP_
#define SCAV_SERVER_GAME_FIELD_HPP_

#include <SFML/Network.hpp>
#include "game_object.hpp"
#include "physics_object.hpp"
#include <map>
#include <list>
#include <ctime>

class GameField {
 private:
	std::map<int, Player*> players;
	std::map<int, PhysicsObject*> objects;
	std::list<Bullet*> bullets;
	StaticObject* borders[4];
	std::clock_t start_time;
	
	b2World* world;
	sf::Packet state_packet;
	std::map<int, sf::Packet*> private_packets;
 public:
	GameField();
	~GameField();
	void add_player(int cl_id);

	void add_bullet(Bullet* bullet);
	void add_object(PhysicsObject* obj);

	void delete_player(int cl_id);
	void delete_bullet(Bullet* b);
	void delete_object(int id);
	
	void step();
	void reset();
	void restart();
	
	sf::Packet* add_private_packet(int cl_id);
	sf::Packet* get_objects(bool reset);

	std::map<int, sf::Packet*>::iterator p_packets_begin();
	std::map<int, sf::Packet*>::iterator p_packets_end();

	PhysicsObject* get_object(int id);
	Player* get_player(int cl_id);
	b2World* get_physics_world();
	sf::Packet* get_state_packet();
	b2World* get_world();
};

#endif