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

void Connector::send(sf::Packet* packet) {
	this->socket.send(*packet);
}


/*void Connector::get() {
	int online=1;
	while(online) {
		sf:Int16 actid = 0;
		sf:Int32 obj = 0;
		float x = 0;
		float y = 0;
		sf::Packet packet;
		this->socket.receive(packet);
		packet >> actid >> obj >> x >> y;
		switch ( actid ) {
			case 1:
				{
					Action action = MoveAction(x,y);
					field.execute(obj, action);
					break;
				}
			default:
				break;
		}
		sleep (20);
	}
}*/

/*void Connector::send(sf::packet& packet) {
	int online=1;
	while(online) {
		sf::Uint8 keyBoardMove=0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			keyBoardMove=1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			keyBoardMove=2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			keyBoardMove=3;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			keyBoardMove=4;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			keyBoardMove=5;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			keyBoardMove=6;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			keyBoardMove=7;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			keyBoardMove=8;
		}
		if(keyBoardMove != 0) {
			sf::Packet packet;
			packet << keyBoardMove;
			this->socket.send(packet);
		}
		sleep (20);
	}
}*/