#include "scav_game.hpp"
//#include <dos.h>

extern GameField field;

Connector::Connector(const std::string& address, int prt): ip(address), port(prt) {
	this->socket.connect(this->ip, this->port);
}

Connector::~Connector() {
	this->socket.disconnect();
}

sf::Packet* Connector::get() {
	sf::Packet* packet = new sf::Packet();
	this->socket.receive(*packet);
	return packet;
}

bool Connector::send(sf::Packet* packet) {
	if (this->socket.send(*packet)  == sf::Socket::Disconnected) {
		return false;
	}
	return true;
	
}

