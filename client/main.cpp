#include "scav_game.hpp"
#include <thread>
#include <unistd.h>
bool online = true;

void get(Connector* connector, GameField* field) {
	while (online) {
		sf::Packet* packet = connector->get();
		std::cout << "get" << std::endl;



		while (!packet->endOfPacket()) {
			ActionConstructor::execute_action(field, *packet);
			//std::cout << id << std::endl;
		}
		std::cout << "read" << std::endl;
		delete packet;
	}
}

void render(GameField* field) {
	field->render();
	std::cout << "ok2" << std::endl;
}

void send(Connector* connector, GameField* field) {
	while (online) {
		sf::Packet packet;
		if (field->get_action(packet)) {
			connector->send(&packet);
		}
		usleep(20000);
	}
}

int main(int argc, char const *argv[])
{
	if (argc < 3) {
		std::cout << "Input ip and port" << std::endl;
		return -1;
	}

	std::string ip(argv[1]);
	int port = std::stoi(argv[2]);
	GameField field;

	//Удалить
	for (int i = 0; i< 10; ++i) {
		Wall* p = new Wall(200, field.get_physics_world(), b2Vec2(20, 20), b2Vec2(100, 100+i*20));
		Texture* playertexture = new Texture();
		playertexture->loadFromFile("wall.png");
		p->set_sprite(playertexture);
		field.add(p, 200+i);
	}
	//------

	Connector connector(ip, port);

	std::thread get_thread(get, &connector, &field);
	std::thread send_thread(send, &connector, &field);
	std::thread render_thread(render, &field);

	get_thread.join();
	send_thread.join();
	render_thread.join();

	return 0;
}
