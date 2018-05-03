#include "server.hpp"
#include <unistd.h>
#include <iostream>
void interact(Network& net, GameField& gf) {
	b2World* world = gf.get_world();
	ContactListener l;
	world->SetContactListener(&l);
	while (true) {
		ActionContainer* ac = net.get_actions();
		ClientAction* act = ac->pop();

		while (act != nullptr) {
			act->execute(gf);
			delete act;
			act = ac->pop();
		}
		l.execute_actions(gf);
		gf.step();
		
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

	//Временно
	for (int i = 0; i< 10; ++i) {
		StaticObject* s = new StaticObject(200 + i, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(100, 100+i*20));
		gf.add_object(s);
	}
	AidKit* s = new AidKit(300, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(100, 50));
	gf.add_object(s);

	LandingMine* l = new LandingMine(301, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(100, -10));
	gf.add_object(l);

	BulletContainer* b = new BulletContainer(302, gf.get_physics_world(), b2Vec2(20, 20), b2Vec2(160, 30));
	gf.add_object(b);
	//----------------
	Network net(port, &gf);
	
	std::thread interact_thread(interact, std::ref(net), std::ref(gf));
	net.listen();
	

	interact_thread.join();
	return 0;
}