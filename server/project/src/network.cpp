#include <server.hpp>

Network::Network(int port) {
	listener.listen(port);
}

sf::Packet* Network::get_actions() {

}

void Network::listen() {
	sf::TcpSocket* socket = new sf::TcpSocket();
	listener.accept(socket);
}
