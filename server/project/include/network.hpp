#ifndef SCAV_SERVER_NETWORK_HPP_
#define SCAV_SERVER_NETWORK_HPP_

#include "action_container.hpp"
#include <SFML/Network.hpp>
#include <thread>
#include <list>
#include <map>

class Network {
 private:
 	int port;

	sf::TcpListener listener;
	std::map<int, sf::TcpSocket*> sockets;
	std::list<std::thread*> get_threads;
	SafeActionContainer container;

	void recieve(int cl_id, sf::TcpSocket* socket, SafeActionContainer& container);
	void send_to_socket(sf::TcpSocket* socket, sf::Packet* packet);
 public:
	Network(int _port);
	~Network();
	ActionContainer* get();
	void listen();
	void translate(sf::Packet& packet);
};

#endif