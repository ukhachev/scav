#ifndef SCAV_SERVER_NETWORK_HPP_
#define SCAV_SERVER_NETWORK_HPP_

#include "action_container.hpp"
#include "game_field.hpp"
#include <SFML/Network.hpp>
#include <thread>
#include <list>
#include <map>

class Network {
 private:
 	int port;
 	GameField* field;
 	bool online;
	std::map<int, sf::TcpSocket*> sockets;
	std::list<std::thread*> get_threads;
	SafeActionContainer container;
	void delete_client(int cl_id);
	static void receive(int cl_id, sf::TcpSocket* socket, SafeActionContainer& container, const bool* online, Network* net);
	void send_to_socket(sf::TcpSocket* socket, sf::Packet* packet);
 public:
	Network(int _port, GameField* _field);
	~Network();

	ActionContainer* get_actions();
	void listen();
	void translate(sf::Packet* packet);

};

#endif