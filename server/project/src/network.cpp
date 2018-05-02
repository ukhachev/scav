#include "network.hpp"
#include "client_action_constructor.hpp"
#include "client_action.hpp"
#include <iostream>

Network::Network(int _port, GameField* _field): port(_port), field(_field), online(false) {
}

Network::~Network() {
	for (auto i = get_threads.begin(); i != get_threads.end(); ++i) {
		(*i)->join();
		delete *i;
	}
	for (auto i = sockets.begin(); i != sockets.end(); ++i) {
		i->second->disconnect();
		delete i->second;
	}
}

void Network::listen() {
	sf::TcpListener listener;
	online = true;
	listener.listen(port);
	while (online) {
		sf::TcpSocket* socket = new sf::TcpSocket();

		listener.accept(*socket);

		int cl_id = 0;
		auto i = sockets.rbegin();

		if (i != sockets.rend()) {
			cl_id = i->first + 1;
		}
		sf::Packet player_set;
		for (auto i = sockets.begin(); i != sockets.end(); ++i) {
			std::cout << "q" << std::endl;
			player_set << 100 << i->first;
		}

		sf::Packet* object_set = field->get_objects();

		sockets.emplace(cl_id, socket);

		std::thread* client_thread = 
			new std::thread(receive, cl_id, socket, std::ref(container), &online, this);
		get_threads.push_front(client_thread);

		
		player_set << 101 << cl_id;

		//sf::Packet* obj_packet = field->get_objects();
		
		send_to_socket(socket, &player_set);
		send_to_socket(socket, object_set);
		delete object_set;
		//delete obj_packet;

		container.add_action(new PlayerJoinedAction(cl_id));

		std::cout << "joined  " 
		<< cl_id << " : " << socket->getRemoteAddress() << std::endl;
	}
}

static void send(sf::TcpSocket* socket, sf::Packet* packet) {
	socket->send(*packet);
	delete packet;
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
			net->delete_client(cl_id);
			return;
		}
		while (!packet.endOfPacket()) {
			ClientAction* act = 
				ClientActionConstructor::construct(cl_id, packet);
			container.add_action(act);
		}
	}
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