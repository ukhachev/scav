#ifndef SCAV_SERVER_CLIENT_ACTION_CONSTRUCTOR_HPP_
#define SCAV_SERVER_CLIENT_ACTION_CONSTRUCTOR_HPP_

#include "client_action.hpp"
#include <SFML/Network.hpp>

class ClientActionConstructor {
 public:
	static ClientAction* construct(int cl_id, sf::Packet& packet);
};

#endif
