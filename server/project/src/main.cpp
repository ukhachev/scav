#include "server.hpp"
#include <unistd.h>
#include <iostream>
#include <string>

bool online = true;
bool need_restart = false;

void restart_game(Network& net, GameField& gf) {
	gf.reset();
	gf.restart();
	need_restart = false;
	MapBuilder::build(gf);
	sf::Packet* obj_packet = gf.get_objects();
	net.translate(gf.get_state_packet());
	net.translate(obj_packet);
	delete obj_packet;
}

void interact(Network& net, GameField& gf) {
	b2World* world = gf.get_world();
	ContactListener l;
	world->SetContactListener(&l);

	while (online) {
		ActionContainer* ac = net.get_actions();
		ClientAction* act = ac->pop();

		while (act != nullptr) {
			act->execute(gf);
			delete act;
			act = ac->pop();
		}

		if (need_restart) {
			restart_game(net, gf);
		}
		else {
			l.execute_actions(gf);
			gf.step();
			net.translate(gf.get_state_packet());
		}
		
		
		gf.reset();
		delete ac;
		usleep(19000);
	}
}

void listen(Network& net) {
	net.listen();
}

int main()
{
	int port = 55503;
	GameField gf;

	MapBuilder::build(gf);
	Network net(port, &gf);
	
	std::thread interact_thread(interact, std::ref(net), std::ref(gf));
	std::thread listen_thread(listen, std::ref(net));
	
	std::string cmd;
	while (cmd != "quit" && cmd != "q") {
		std::cin >> cmd;
		if (cmd == "reset") {
			std::cout << "Reseting game..." << std::endl;
			need_restart = true;
		}
	}
	online = false;
	net.stop();

	listen_thread.join();
	interact_thread.join();
	return 0;
}