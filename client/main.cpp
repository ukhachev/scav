#include "scav_game.hpp"
#include "Box2D/Box2D.h"
#include <thread>
#include <unistd.h>
#include <mutex>
#include "textures.hpp"
#include <SFML/Audio.hpp>
bool online = true;
Textures* textures;
Animations* animations;

void get(Connector* connector, GameField* field) {
	while (online) {
		sf::Packet* packet = connector->get();

		while (!packet->endOfPacket()) {
			ActionConstructor::execute_action(field, *packet, textures, animations);
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

void send(Connector* connector, GameField* field, std::string& nick) {
	sf::Packet nick_packet;
	nick_packet << 10 << nick;
	connector->send(&nick_packet);

	while (online) {
		sf::Packet packet;
		if (field->get_action(packet)) {
			if (!connector->send(&packet)) {
				online =false;
			}
		}
		usleep(20000);
	}
}

int main(int argc, char const *argv[])
{
	textures = new Textures("textures.txt");
    animations = new Animations("animations.txt");
    GameField field;
    std::string name = "client";
    std::string ip;
    int port = 55503;

	sf::SoundBuffer buffer;
    buffer.loadFromFile("back.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(90);
    sound.setLoop(true);
    sound.play();

	if (argc < 4) {
		std::cout << "Input ip, port and nickname" << std::endl;
		Menu menu(field.get_window(), "scav_bg.jpg", "minecraft.otf");
		menu.draw();
		name = menu.get_name();
		ip = menu.get_ip();
		port = menu.get_port();
	}
	else {
		ip = argv[1];
		port = std::stoi(argv[2]);
		name = argv[3];
	}


	field.get_window()->setMouseCursorVisible(0);
	Connector connector(ip, port);

	std::thread get_thread(get, &connector, &field);
	std::thread send_thread(send, &connector, &field, std::ref(name));
	std::thread render_thread(render, &field);

	get_thread.join();
	send_thread.join();
	render_thread.join();
	delete textures;
    delete animations;
	return 0;
}
