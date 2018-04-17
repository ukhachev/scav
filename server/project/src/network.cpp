#include <server.hpp>

Network::Network(int port) {
	listener.listen(port);
}

void Network::listen(bool* online) {
	while (*online) {
		sf::TcpSocket* socket = new sf::TcpSocket();
		
		listener.accept(socket);
		int cl_id = sockets.rbegin()->first + 1;
		
		sf::Packet player_joined;

		container.add_action(cl_id, new PlayerJoinedAction());

		sockets.insert(cl_id, socket);
		std::thread* client_thread = new std::thread(recieve, cl_id, socket, container);

		sf::Packet player_set;

		player_set << 101 << cl_id;
		get_threads.push_front(client_thread);
		send_to_socket(socket, player_set);
		
	}
}

void Network::send_to_socket(sf::TcpSocket* socket, sf::Packet* packet) {
	socket.send(*packet);
	delete packet;
}

void Network::translate(sf::Packet& packet) {
	for (auto i = sockets.begin(); i != sockets.end(); ++i) {
		sf::packet* new_packet = new packet(packet);
		std::thread send_thread(send_to_socket, i->second, new_packet);
		send_thread.detach();
	}
}

void Network::recieve(int cl_id, sf::TcpSocket* socket, SafeActionContainer& container) {
	container.add
}