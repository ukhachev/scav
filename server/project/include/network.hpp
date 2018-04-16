#ifndef SCAV_SERVER_NETWORK_HPP_
#define SCAV_SERVER_NETWORK_HPP_

#include <action_container.hpp>
#include <SFML/Network.hpp>
#include <thread>

class Network {
 private:
	sf::TcpListener listener;
	std::list<std::thread> sockets;

 public:
	Network(int port);
	~Network();
	sf::Packet* get(sf::TcpSocket& socket);
	void listen();
	void send(sf::packet& packet);
	get_actions();
};

#endif