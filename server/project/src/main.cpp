#include "server.hpp"
#include <unistd.h>
#include <iostream>
void interact(Network& net, GameField& gf) {
	while (true) {
		ActionContainer* ac = net.get_actions();
		ClientAction* act = ac->pop();

		while (act != nullptr) {
			act->execute(gf);
			delete act;
			act = ac->pop();
		}

		net.translate(gf.get_state_packet());
		gf.reset();
		delete ac;
		usleep(19000);
	}
}

int main()
{
	int port = 55503;
	GameField gf;
	Network net(port, &gf);
	
	std::thread interact_thread(interact, std::ref(net), std::ref(gf));
	net.listen();
	

	interact_thread.join();
	return 0;
}