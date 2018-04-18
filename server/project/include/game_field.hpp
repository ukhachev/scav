#ifndef SCAV_SERVER_GAME_FIELD_HPP_
#define SCAV_SERVER_GAME_FIELD_HPP_

#include <SFML/Network.hpp>
#include "game_object.hpp"
#include <map>

class GameField {
 private:
	std::map<int, Player*> players;
	std::map<int, PhysicsObject*> objects;

	sf::Packet state_packet;
	std::map<int, sf::Packet*> private_packets;
 public:
	GameField();
	~GameField();
	void add_player(int cl_id);
	void add_object(PhysicsObject* obj);
	void delete_player(int cl_id);
	void reset();

	sf::Packet* add_private_packet(int cl_id);

	std::map<int, sf::Packet*>::iterator p_packets_begin();
	std::map<int, sf::Packet*>::iterator p_packets_end();
	PhysicsObject* get_object(int id);
	Player* get_player(int cl_id);
	sf::Packet* get_state_packet();
};

#endif