#include "client_action_constructor.hpp"

ClientAction* ClientActionConstructor::construct(int cl_id, sf::Packet& packet) {
	int id = 0;
	packet >> id;
	switch (id) {
		case 100:
			return new PlayerJoinedAction(cl_id);
		case 1:
			return new MoveAction(cl_id, packet);
		case 14:
			return new ShotAction(cl_id, packet);
	}
	return nullptr;
}