#include "server.hpp"
#include <unistd.h>
#include <iostream>
void interact(Network& net, GameField& gf) {
	while (true) {
		ActionContainer* ac = net.get_actions();
		for (auto i = ac->begin(); i != ac->end(); ++i) {
			(*i)->execute(gf);
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