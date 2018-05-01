
#include <SFML/Network.hpp>
#include <iostream>
int main(int argc, char const *argv[])
{
	sf::TcpListener listener;
	listener.listen(55002);
// Wait for a connection
	sf::TcpSocket socket;
	listener.accept(socket);
	std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
// Receive a message from the client
	sf::Packet packet;
	packet << 1 << 2 << 3;
	
// Send an answer
	socket.send(packet);
	socket.disconnect();
	listener.close();
	return 0;
}

