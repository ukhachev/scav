
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <thread>
#include <list>
#include <scav_game.hpp>
#include <dos.h>

GameField field();

int main(int argc, char const *argv[])
{
	Connector connector("127.0.0.1", 55001);
	std::thread getThread(connector.get);
	thr.join();
	std::thread getThread(field.render);
	thr.join();
	std::thread getThread(connector.send);
	thr.join();
	return 0;
}

