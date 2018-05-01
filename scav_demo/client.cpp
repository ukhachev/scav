
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <unistd.h>
#include <iostream>
#include <thread>
int online = 1;
void receive(sf::TcpSocket& socket) {
	while (online) {
		sf::Packet packet;
		socket.receive(packet);
		int id = 0;
		packet >> id;
		std::cout << id << std::endl;
	}
}
int main(int argc, char const *argv[])
{
	sf::TcpSocket socket;
 	socket.connect("127.0.0.1", 55503);

	std::thread receive_thread(receive, std::ref(socket));

	float x = 0, y = 0, z = 0;
	for (int i = 0; i < 600; ++i)
	{
		sf::Packet packet;
		packet << 1 << x << y << z;
		socket.send(packet);
		x+=i;
		y++;
		z--;
		usleep(19000);

	}
	online = 0;
	receive_thread.join();
	socket.disconnect();
	return 0;
}

