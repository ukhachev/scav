#ifndef SCAV_CONNECTOR_HPP_
#define SCAV_CONNECTOR_HPP_

#include <SFML/Network.hpp>
#include <iostream>
#include <map>
#include <string>
#include "game_object.hpp"

class Connector {
private:
	sf::TcpSocket socket;
	std::string ip;
	int port;
public:
	Connector(const std::string& address, int prt);
	~Connector();
	sf::Packet* get();
	void send(sf::Packet* packet);
};

#endif