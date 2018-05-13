#ifndef SCAV_SERVER_NETWORK_HPP_
#define SCAV_SERVER_NETWORK_HPP_

#include "action_container.hpp"
#include "game_field.hpp"
#include <SFML/Network.hpp>
#include <thread>
#include <list>
#include <map>
#include <vector>
class Network {
 private:
 	int port;
 	GameField* field;
 	bool online;

 	size_t min_count;
 	std::map<int, sf::TcpSocket*> sockets;
	SafeActionContainer container;

	void delete_client(int cl_id);
	static void receive(int cl_id, sf::TcpSocket* socket, SafeActionContainer& container, const bool* online, Network* net);
	void send_to_socket(sf::TcpSocket* socket, sf::Packet* packet);
	void start_game();
 public:
	Network(int _port, GameField* _field, size_t _min_count);
	~Network();

	ActionContainer* get_actions();
	void listen();
	void translate(sf::Packet* packet);
	void stop();

};

#endif