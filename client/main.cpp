#include <scav_game.hpp>
#include <thread>

bool online = true;

void get(Connector& connector, GameField& field) {
	while (online) {
		Action* act = connector.get();
		field.execute(act);
		delete act;
	}
}

void render(GameField& field) {
	while (online) {
		field.render();
	}
}

void send(Connector& connector, GameField& field) {
	while (online) {
		sf::packet* act = field.get_action();
		connector.send(packet);
		//sleep(20);
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
	Connector connector(ip, port);

	std::thread get_thread(get, connector, field);
	std::thread send_thread(send, connector, field);
	std::thread render_thread(render, field);

	get_thread.join();
	send_thread.join();
	render_thread.join();

	return 0;
}