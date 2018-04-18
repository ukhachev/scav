
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
		while (!(packet.endOfPacket())) {
			int id = 0;
			packet >> id;
			int go_id = 0;
			float x = 0, y = 0, z = 0;
			if (id == 1) {
				packet >> go_id >> x >> y >> z;
				std::cout << go_id << " "; //<< x << " " << y << " " << z<< std::endl;
			}
		}
		std::cout << std::endl;
	}
}
int main()
{
	sf::TcpSocket socket;
 	socket.connect("127.0.0.1", 55503);

	std::thread receive_thread(receive, std::ref(socket));

	float x = 1, y = 1, z = 1;
	for (int i = 0; i < 6000; ++i)
	{
		usleep(20000);
		sf::Packet packet;
		packet << 1 << x << y << z;
		socket.send(packet);
		x+=0.1f;
		y++;
		z--;
	}
	online = 0;
	receive_thread.join();
	socket.disconnect();
	return 0;
}