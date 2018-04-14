
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
int main(int argc, char const *argv[])
{
	sf::TcpSocket socket;
 	socket.connect("127.0.0.1", 55001);
	int x = 0, y = 0, z = 0;
	sf::Packet packet;
	socket.receive(packet);
	packet >> x >> y >> z;
	std::cout << x << y << z;
	socket.disconnect();
	return 0;
}

