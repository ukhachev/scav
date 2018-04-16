#include <SFML/Network.hpp>
class ClientAction {
 private:
 	int id;
 public:
 	int get_id();
 	void execute(GameObject* obj);
};


class Network {
 private:
 	sf::TcpListener listener;
 	std::list<sf::TcpSocket*> clients;
 public:
	Network(int port);
	~Network();
	void send_packet(sf::packet& packet);
	get_actions();
}
