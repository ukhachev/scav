#include "scav_game.hpp"
#include "Box2D/Box2D.h"
#include <thread>
#include <unistd.h>
#include <mutex>
#include "textures.hpp"
bool online = true;
Textures* textures;

void get(Connector* connector, GameField* field) {
	while (online) {
		sf::Packet* packet = connector->get();

		while (!packet->endOfPacket()) {
			ActionConstructor::execute_action(field, *packet, textures);
		}
		delete packet;
	}
}

void render(GameField* field) {
	b2World* world = field->get_physics_world();
	std::mutex& mtx = field->get_mutex();
	

	ContactListener l;
	world->SetContactListener(&l);
  		
	while (field->render()) {
		mtx.lock();
        l.execute_actions(*field);
        world->Step(1/60.f, 8, 3);
        mtx.unlock();
	}

	online = false;
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
	textures = new Textures("textures.txt");

	std::string ip(argv[1]);
	int port = std::stoi(argv[2]);
	GameField field;

	//Удалить
	for (int i = 0; i< 10; ++i) {
		Wall* p = new Wall(200, field.get_physics_world(), b2Vec2(20, 20), b2Vec2(100, 100+i*20));
		p->set_sprite(textures->get_texture(2));
		field.add_wall(p, 200+i);
	}
	//------

	Connector connector(ip, port);

	std::thread get_thread(get, &connector, &field);
	std::thread send_thread(send, &connector, &field);
	std::thread render_thread(render, &field);

	get_thread.join();
	send_thread.join();
	render_thread.join();
	delete textures;
	return 0;
}
