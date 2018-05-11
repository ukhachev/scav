#include "network.hpp"
#include "client_action_constructor.hpp"
#include "client_action.hpp"
#include <iostream>
#include <unistd.h>
Network::Network(int _port, GameField* _field, size_t _min_count): 
			port(_port), field(_field), online(false), min_count(_min_count) {
}

Network::~Network() {
	online = false;
	while(!sockets.empty()) {
		usleep(10000);
	}
	std::cout << "all resources are cleaned" << std::endl;
}

static void send(sf::TcpSocket* socket, sf::Packet* packet) {
	socket->send(*packet);
	delete packet;
}

void Network::stop() {
	online = false;
}
void Network::start_game() {
		for (auto i = sockets.begin(); i != sockets.end(); ++i) {
			container.add_action(new PlayerJoinedAction(i->first));
		}

		field->set_start(true);
		sf::Packet start_game_packet;
		start_game_packet << 50 << 1;
		std::cout << "Game started" << std::endl;
		translate(&start_game_packet);
}
void Network::listen() {
	sf::TcpListener listener;
	listener.setBlocking(false);
	online = true;
	listener.listen(port);

	sf::TcpSocket* socket = new sf::TcpSocket();

	while (online) {
		if (listener.accept(*socket) != sf::Socket::Done) {
			if (!field->get_start() && sockets.size() >= min_count) {
				start_game();
			}
			usleep(20000);
			continue;
		}

		int cl_id = 0;
		auto i = sockets.rbegin();

		if (i != sockets.rend()) {
			cl_id = i->first + 1;
		}

		sf::Packet player_set;
		for (auto i = sockets.begin(); i != sockets.end(); ++i) {
			player_set << 100 << i->first;
		}

		sf::Packet* object_set = field->get_objects(false);

		sockets.emplace(cl_id, socket);

		std::thread client_thread(receive, cl_id, socket, std::ref(container), &online, this);
		client_thread.detach();

		player_set << 101 << cl_id;
		
		send_to_socket(socket, &player_set);
		send_to_socket(socket, object_set);
		delete object_set;

		std::cout << "joined  " 
		<< cl_id << " : " << socket->getRemoteAddress() << std::endl;

		socket = new sf::TcpSocket();
	}
	delete socket;
}



void Network::send_to_socket(sf::TcpSocket* socket, sf::Packet* packet) {
	sf::Packet* p = new sf::Packet(*packet);
	std::thread send_thread(send, socket, p);
	send_thread.detach();
}

void Network::translate(sf::Packet* packet) {
	if (packet->endOfPacket()) {
		return;
	}

	for (auto i = sockets.begin(); i != sockets.end(); ++i) {
		send_to_socket(i->second, packet);
	}
}

void Network::receive(int cl_id, sf::TcpSocket* socket, SafeActionContainer& container, const bool *online, Network* net) {
	while (*online) {
		sf::Packet packet;
		if (socket->receive(packet) == sf::Socket::Disconnected) {
			break;
		}
		while (!packet.endOfPacket()) {
			ClientAction* act = 
				ClientActionConstructor::construct(cl_id, packet);
			container.add_action(act);
		}
	}
	net->delete_client(cl_id);
}

ActionContainer* Network::get_actions() {
	return container.get_actions();
}

void Network::delete_client(int cl_id) {
	auto i = sockets.find(cl_id);
	ClientAction* left_act = new PlayerLeftAction(cl_id);
	container.add_action(left_act);
	
	std::cout << "disconnect " << cl_id <<std::endl;
	delete i->second;
	sockets.erase(i);

}